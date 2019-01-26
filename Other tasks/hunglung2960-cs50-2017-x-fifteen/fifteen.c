/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9


// dimensions
int d;
// board
int board[DIM_MAX][DIM_MAX];


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // TODO
    int tile = ((d*d)-1);
    for (int p = 0; p < d; p++)
    {
        for (int o = 0; o < d; o++)
        {
            board [p][o] = tile;
            tile = tile - 1;
        }
    }
    if ((d*d-1) % 2 == 1)
    {
        board [d-1][d-2] = 2;
        board [d-1][d-3] = 1;
    }

}

/**
 * Prints the board in its current state.
 */
 //checked>>>no problem at all.
void draw(void)
{
    //TODO
    for (int z = 0; z < d; z++)
    {
        for (int x = 0; x < d; x++)
        {
            if (board[z][x] == 0)
            {
                printf("_ ");
            }
            else
            {
                printf("%d ", board[z][x]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // TODO
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            int StoreOrigin = 0;
            if (board[r][c] == tile)
            {
                if (r < (d-1) && board[r+1][c] == 0)
                {
                    StoreOrigin = board[r][c];
                    board[r+1][c] = StoreOrigin;
                    board[r][c] = 0;
                    return true;
                }
                if (r > 0 && board[r-1][c] == 0)
                {
                    StoreOrigin = board[r][c];
                    board[r-1][c] = StoreOrigin;
                    board[r][c] = 0;
                    return true;
                }
                if (c < (d-1) && board[r][c+1] == 0)
                {
                    StoreOrigin = board[r][c];
                    board[r][c+1] = StoreOrigin;
                    board[r][c] = 0;
                    return true;
                }
                if (c > 0 && board[r][c-1] == 0)
                {
                    StoreOrigin = board[r][c];
                    board[r][c-1] = StoreOrigin;
                    board[r][c] = 0;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */

 //This is verified as being correct.
bool won(void)
{
    // TODO
    int R;
    int C;
    int Array4Check[d][d];
    int fillin = 0;
    for (R = 0; R < d; R++)
    {
        for (C = 0; C < d; C++)
        {
            fillin = fillin + 1;
            Array4Check[R][C] = fillin;
        }

    }
    Array4Check[d-1][d-1] = 0;

    int correct = 0;
    for (int Row = 0; Row < d; Row++)
    {
        for (int Column = 0; Column < d; Column++)
        {
            if (Array4Check[Row][Column] == board[Row][Column])
            {
                correct = correct + 1;
            }
        }
    }
    if (correct == (d*d) && board[d-1][d-1] == 0)
    {
        return true;
    }
    return false;
}
