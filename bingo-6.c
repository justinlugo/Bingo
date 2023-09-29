#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define FREE 2
#define MINVAL 1
#define MAXVAL 75
#define VALUES 25
#define SHIFT 1
#define SCALE 15
#define FALSE 0
#define TRUE 1
#define BINGO 5

#define B 0
#define I 1
#define N 2
#define G 3
#define O 4
#define DOB 'X'

// function prototypes
void welcomeScreen ();
void displayExplicitCard();
void clearScreen();
void displayCard();
void displayRandomCard();
void fillCardRand(int card[ROWS][COLS], int used[MAXVAL]);
void setValue(int card[ROWS][COLS], int used[MAXVAL], int row, int col);
void displayBingoCard(int card[ROWS][COLS]);
void initializeArrays(int used[MAXVAL], int called[MAXVAL], char result[ROWS][COLS]);
void play(int card[ROWS][COLS], int called[MAXVAL], char result[ROWS][COLS]);
int callNumber(int called[MAXVAL]);
void checkNumber(char letter, int number, int card[ROWS][COLS], char result[ROWS][COLS]);
void displayNumber(char letter, int number);
bool horizontalLine(char result[ROWS][COLS]);


// main function
int main()
{
    /*This is the main function that will go through all of the functions below in order to run the program fully*/
    int card[ROWS][COLS];
    int used[MAXVAL];
    int called[MAXVAL];
    char result[ROWS][COLS];

    srand(time(0));

    // call function welcomeScreen
    welcomeScreen();
    // call function clearScreen
    clearScreen();
    // call function displayExplicitBingoCard
//    displayExplicitCard();
//
//    clearScreen();
//
//    displayCard();
//
//    clearScreen();
//
//    fillCard(card);
//
//    displayBingoCard(card);
//
//    clearScreen();

    initializeArrays(used, called, result);

    fillCardRand(card, used);

    displayBingoCard(card);

    play(card, called, result);
    // program executed successfully
    return 0;
}

// welcomeScreen function displays the BINGO logo and rules of the game
void welcomeScreen ()
{
    /*This is the welcome screen that will welcome the player*/
	printf ("\t\t\tBBBBB   II  NN     NN    GGGGG    OOOO  \n");
	printf ("\t\t\tBB  BB  II  NN N   NN  GG        OO  OO \n");
	printf ("\t\t\tBBBBB   II  NN  N  NN  GG        OO  OO \n");
	printf ("\t\t\tBB  BB  II  NN   N NN  GG  GGGG  OO  OO \n");
	printf ("\t\t\tBBBBB   II  NN     NN   GGGGGG    OOOO  \n");
	printf ("\n\n");//
	printf ("RULES OF THE GAME:\n");
    printf("1. A player receives a Bingo card\n");
    printf("2. Each card has a random placement of numbers for each column, B, I, N. G, O\n");
    printf("\t Column B contains values 1 - 15\n");
    printf("\t Column I contains values 16 - 30\n");
    printf("\t Column N contains values 31 - 45 in addition to a FREE space\n");
    printf("\t Column G contains values 46 - 60\n");
    printf("\t Column O contains values 61 - 75\n");
    printf("3. Various patterns are identified to accomplish a BINGO\n");
    printf("4. Each round of the game will identify which pattern should be accomplished to win a BINGO\n");
    printf("5. Winning numbers are randomly selected during play\n");
    printf("6. Good luck!\n");
}

// function displayExplicitBingoCard displays a hardcoded version of a bingo card
void displayExplicitCard()
{
    //Displays the normal card
    printf("|---------------------------------------|\n");
    printf("|   B   |   I   |   N   |   G   |   O   |\n");
    printf("|---------------------------------------|\n");
    printf("|   15  |   16  |   31  |   46  |   61  |\n");
    printf("|---------------------------------------|\n");
    printf("|   2   |   23  |   45  |   60  |   75  |\n");
    printf("|---------------------------------------|\n");
    printf("|   5   |   20  |  FREE |   51  |   68  |\n");
    printf("|---------------------------------------|\n");
    printf("|   12  |   27  |   40  |   55  |   70  |\n");
    printf("|---------------------------------------|\n");
    printf("|   9   |   30  |   37  |   49  |   64  |\n");
    printf("|---------------------------------------|\n");
}

void displayCard()
{
    //Displays the Card
    int row;
    int col;

    printf("|---------------------------------------|\n");
    printf("|   B   |   I   |   N   |   G   |   O   |\n");
    printf("|---------------------------------------|\n");

    for(row = 0; row < ROWS; row++)
    {
        printf("|");

        for(col = 0; col < COLS; col++)
        {
            if(row == FREE && col == FREE)
            {
                printf("  FREE |");
            }
            else
            {
                printf("%s%-3d", "   ", 15);
                printf(" |");
            }
        }

        printf("\n");
        printf("|---------------------------------------|\n");
    }
}

// function clearScreen clears the screen for display purposes
void clearScreen()
{
    //Clears the screen and advances the program
    printf("\n\t\t\t\tHit <ENTER> to continue!\n");

	char enter;
	scanf("%c", &enter );

	// send the clear screen command Windows
    system("cls");
    // send the clear screen command for UNIX flavor operating systems
    // system("clear");
}

void fillCard(int card[ROWS][COLS])
{
    //This function fills the bingo card array with numbers
    int row;
    int col;

    for(row = 0; row < ROWS; row++)
    {
        for(col = 0; col < COLS; col++)
        {
            card[row][col] = (col + 1) * SCALE - row;
        }
    }
}

void fillCardRand(int card[ROWS][COLS], int used[MAXVAL])
{
    //This function fills the bingo card with randomized numbers
    int row;
    int col;

    for(col = 0; col < COLS; col++)
    {
        for(row = 0; row < ROWS; row++)
        {
            // if location is the FREE space, set the value to 0
            if(row == FREE && col == FREE)
            {
                card[row][col] = 0;
            }
            else
            {
                setValue(card, used, row, col);
            }
        }

    }
}

void setValue(int card[ROWS][COLS], int used[MAXVAL], int row, int col)
{
    //Sets the values within the card array
    int num;
    int base;
    int idx;

    base = SCALE * col;

    num = (rand() % SCALE) + SHIFT + base;
    idx = num - SHIFT;

    if(used[idx] == FALSE)
    {
        used[idx] = TRUE;
        card[row][col] = num;
    }
    else
    {
        // already used the number, try again
        setValue(card, used, row, col);
    }
}

void displayBingoCard(int card[ROWS][COLS])
{
    //Displays a bingo card using the values set by the card array
    int row;
    int col;

    printf("|---------------------------------------|\n");
    printf("|   B   |   I   |   N   |   G   |   O   |\n");
    printf("|---------------------------------------|\n");

    for(row = 0; row < ROWS; row++)
    {
        printf("|");

        for(col = 0; col < COLS; col++)
        {
            if(row == FREE && col == FREE)
            {
                printf("  FREE |");
            }
            else
            {
                printf("%s%-3d", "   ", card[row][col]);
                printf(" |");
            }
        }

        printf("\n");
        printf("|---------------------------------------|\n");
    }
}

void displayBingoCardPlay(int card[ROWS][COLS], char result[ROWS][COLS])
{
    //displays a *new* bingo card that will be used to play
    int row;
    int col;

    printf("|---------------------------------------|\n");
    printf("|   B   |   I   |   N   |   G   |   O   |\n");
    printf("|---------------------------------------|\n");

    for(row = 0; row < ROWS; row++)
    {
        printf("|");

        for(col = 0; col < COLS; col++)
        {
            if(result[row][col] == DOB)
            {
                printf("%s%-3c", "   ", result[row][col]);
            }
            else if(row == FREE && col == FREE)
            {
                printf("  FREE");
            }
            else
            {
                printf("%s%-3d", "   ", card[row][col]);
            }

            printf(" |");

        }

        printf("\n");
        printf("|---------------------------------------|\n");
    }
}
void initializeArrays(int used[MAXVAL], int called[MAXVAL], char result[ROWS][COLS])
{
    //creates an array utilizing arrays used, called, and result
    int row;
    int col;

    for (row = 0; row < ROWS; row++)
    {
        for(col = 0; col < COLS; col++)
        {
            if(row == FREE && col == FREE)
                result[row][col] = 'X';
            else
                result[row][col] = ' ';
        }
    }

    for(col = 0; col < MAXVAL; col++)
    {
        used[col] = FALSE;
        called[col] = FALSE;
    }
}

void play(int card[ROWS][COLS], int called[MAXVAL], char result[ROWS][COLS])
{
    //This is the function that moves along the actual game, since it calls numbers
    int number;
    bool bingo = false;
    char letter;
    int counter = 0;

    printf("\n\nLet's play BINGO!\n\n");

    while(!bingo)
    {
        number = callNumber(called);

        if(number >= 1 && number <= 15)
        {
            letter = 'B';
        }
        else if(number >= 16 && number <= 30)
        {
            letter = 'I';
        }
        else if(number >= 31 && number <= 45)
        {
            letter = 'N';
        }
        else if(number >= 46 && number <= 60)
        {
            letter = 'G';
        }
        else if(number >= 61 && number <= 75)
        {
            letter = 'O';
        }

        displayNumber(letter, number);
        checkNumber(letter, number, card, result);
        displayBingoCardPlay(card, result);

        bingo = horizontalLine(result);
    }
    printf("BINGO! You have BINGO! You won $1 MILLION DOLLARS!\n");
}

bool horizontalLine(char result[ROWS][COLS]){
    /*This will determine if there is a horizontal bingo or not,
    and will continue running until bingo is reached*/
    bool bingo;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (result[i][j] == 'X' && result[i][j + 1] == 'X' && 
                result[i][j + 2] == 'X' && result[i][j + 3] == 'X' &&
                result[i][j + 4] == 'X')
                {
                    return true;
                }
        }
    }
}

void displayNumber(char letter, int number)
{
    //Displays the number and letters called.
    printf("\n%c-%d... ", letter, number);
    printf("%c... ", letter);
    printf("%d\n", number);

    char enter;
    scanf("%c", &enter );

}

void checkNumber(char letter, int number, int card[ROWS][COLS], char result[ROWS][COLS])
{
    //Checks for used numbers.
    int row;
    int col;

    switch(letter)
    {
        case 'B':
            col = B;
            break;
        case 'I':
            col = I;
            break;
        case 'N':
            col = N;
            break;
        case 'G':
            col = G;
            break;
        case 'O':
            col = O;
            break;
    }

    for(row = 0; row < ROWS; row++)
    {
        if(card[row][col] == number)
        {
            result[row][col] = DOB;
        }
    }
}

int callNumber(int called[MAXVAL])
{
    //Calls numbers and sets them into value
    int num;
    int idx;

    idx = (rand() % MAXVAL);
    num = idx + SHIFT;

    // base case to stop recursion
    if(called[idx] == FALSE)
    {
        called[idx] = TRUE;
        return num;
    }
    else
    {
        callNumber(called);
    }
}
