import random
import cs50

#Instruction of Game
print("Welcome!")
print("This is a game guessing number within range from 1 to 100.")
print("The person who hits the answer will face punishment.")
print("Punishment is to do pushup.")
print("Times = How many times players guess * Pain")

#Set player number.
PlayerNum = cs50.get_int("Number of players:")
Player = []
for i in range(PlayerNum):
    Name = cs50.get_string("Player's Name:")
    Player.append(Name)

#Set the difficulty of consequence of the game.
Pain = cs50.get_int("Pain:")


#initial values
number = random.randint(1,100)
Lowerbound = 1
Upperbound = 100
guess = 0
j = 0

#Print out a list of players
ppl = 1
for player in Player:
    print("Player {} is {}".format(ppl,player))
    ppl +=1

#Game start!
print("{}, You start first.".format(Player[j]))
print("Guess a number between 1 and 100.")
numbertaken = cs50.get_int("number:")

while True:
    if numbertaken >= Upperbound or numbertaken <= Lowerbound:
        print("number must be within the range!")
        print("Guess a number between {} and {}".format(Lowerbound,Upperbound))
        numbertaken = cs50.get_int("number:")
    else:
        if numbertaken != number:
            if number > numbertaken:
                Lowerbound = numbertaken
                print("Guess a number between {} and {}".format(Lowerbound,Upperbound))
            if number < numbertaken:
                Upperbound = numbertaken
                print("Guess a number between {} and {}".format(Lowerbound,Upperbound))

        guess += 1
        j += 1
        j = j % PlayerNum
        print("{},It is your turn.".format(Player[j]))
        if numbertaken == number:
            break
        else:
            numbertaken = cs50.get_int("number:")


print("Bomb!!!!")
print("{} YOU LOCK DOWN!!!".format(Player[j]))
print("{} Pushup!!!!!!!!!".format(guess*Pain))
