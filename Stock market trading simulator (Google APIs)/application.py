from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from passlib.context import CryptContext
from tempfile import mkdtemp
import numbers
from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index(): #DONE!
    #TODO
    #manipulate the data and insert to the html framework
    stocks = db.execute("SELECT * FROM portfolio WHERE id = :id", id = session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
    totals = db.execute("SELECT total FROM portfolio WHERE id = :id", id = session["user_id"])
    Total = 0
    for i in range(len(totals)):
        Total = float(totals[i]["Total"]) + Total

    return render_template("portfolio.html", stocks = stocks, cash = cash[0]["cash"], Total = Total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy(): #DONE!
    #TODO
    """Buy shares of stock."""
    if request.method == "POST":
        #Ensure symbol and share are filled in
        if request.form.get("symbol") == "":
            return apology("must provide symbol")
        elif request.form.get("shares") == "":
            return apology("must provide shares")

        #Ensure share is a positive integer
        shares = float(request.form.get("shares"))
        intchecker = isinstance(shares, float)
        if intchecker == False or shares <= 0:
            return apology("must provide positive integer")

        #Ensure symbol is correct
        symbolchecker = lookup(request.form.get("symbol"))
        if symbolchecker == None:
            return apology("symbol is not valid")

        #Check if user has enough money
        quote = lookup(request.form.get("symbol"))
        name = quote["name"]
        price = quote["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        if cash[0]["cash"] < price:
            return apology("cannot afford")

        #Deduct money from user DB 's cash
        charge = shares * price
        balance = cash[0]["cash"] - charge ##might be a problem here!!!!!
        BalanceInDB = db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = balance, id = session["user_id"])

        #Add the new shares to portfolio DB
        Adder1 = db.execute("INSERT INTO portfolio (Symbol, Name, Shares, Price, Total, id) \
                            VALUES (:Symbol, :Name, :Shares, :Price, :Total, :id)",\
                            Symbol=request.form.get("symbol"), Name=name, Shares=shares, Price=price, Total=charge, id=session["user_id"])

        #Add the transaction to history / create a history DB
        Adder2 = db.execute("INSERT INTO history (Symbol, Shares, Price, id) \
                            VALUES (:Symbol, :Shares, :Price, :id)",\
                            Symbol=request.form.get("symbol"), Shares=shares, Price=price, id=session["user_id"])

        return redirect(url_for("index"))

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history(): #DONE!!
    """Show history of transactions."""
        #TODO
    stocks = db.execute("SELECT * FROM history WHERE id = :id", id = session["user_id"])
    if stocks == "":
        return apology("No History So Far") ##

    return render_template("history.html", stocks = stocks)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")


        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote(): ##DONE!
    """Get stock quote."""

    if request.method == "POST":

        if request.form.get("symbol") == "":
            return apology("must provide a symbol")
        elif lookup(request.form.get("symbol")) == None:
            return apology("must provide a correct symbol")

        symbol = request.form.get("symbol").upper()
        quote = lookup(request.form.get("symbol"))

        return render_template("quoted.html", name = quote["name"], symbol = symbol, price = quote["price"])
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():  ##DONE!
    """Register user."""
    if request.method == "POST":

        # ensure username was submitted
        if request.form.get("username") == "":
            return apology("must provide username")

        # ensure password was submitted
        elif request.form.get("password") == "":
            return apology("must provide password")

        elif request.form.get("password (again)") == "":
            return apology("must type in password again")

        elif request.form.get("password (again)") != request.form.get("password"):
            return apology("must provide the same password")

        result = db.execute("INSERT INTO users (username, hash) \
                         VALUES (:username, :hash)",\
                         username = request.form.get("username"), \
                         hash = pwd_context.hash(request.form.get("password")))

        if not result:
            return apology("username exists already")

        return redirect(url_for("index"))
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    #Drop-down List for symbol
    Symbols = db.execute("SELECT Symbol FROM portfolio WHERE id = :id", id = session["user_id"])
    if request.method == "POST":
        #Ensure not blank
        if request.form.get("shares") == "":
            return apology("must provide shares")

        #Delete the shares from portfolio DB
        Deducter1 = db.execute("DELETE FROM portfolio WHERE Symbol = :Symbol, Shares = :Shares, id = :id", \
                                Symbol=request.args.get("symbolselected"), Shares=request.form.get("shares"), id=session["user_id"])
        #Add cash to user DB's cash
        quote = lookup(request.args.get("symbolselected"))
        name = quote["name"]###
        price = quote["price"]
        shares = float(request.form.get("shares"))
        Profit = shares * price
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        balance = cash[0]["cash"] + Profit
        BalanceInDB = db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = balance, id = session["user_id"])

        #Add the transaction to history DB
        Adder = db.execute("INSERT INTO history (Symbol, Shares, Price, id) \
                            VALUES (:Symbol, :Shares, :Price, :id)",\
                            Symbol=request.args.get("symbolselected"), Shares=shares, Price=price, id=session["user_id"])

        return redirect(url_for("index"))
    else:
        return render_template("sell.html", Symbols = Symbols)

@app.route("/addmoney", methods=["GET", "POST"])
@login_required
def addmoney():
    if request.method == "POST":
        #Ensure amount is filled in
        if request.form.get("money") == "":
            return apology("must provide amount")

        #Ensure amount is a positive integer
        money = float(request.form.get("money"))
        intchecker = isinstance(money, float)
        if intchecker == False or money <= 0:
            return apology("must provide positive integer")

        #Check how much users have
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        addition = cash[0]["cash"] + money

        #Add the new shares to portfolio DB
        Adder1 = db.execute("UPDATE users SET cash=:cash WHERE id=:id",
                            cash=addition, id=session["user_id"])

        return redirect(url_for("index"))

    else:
        return render_template("addmoney.html")