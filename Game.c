#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"
#include <stdlib.h>
#include "Board.h"
#include "Save.h"
#include "Movement.h"
#include <ctype.h>
struct commands availableCommands[1000];
int sizeOfAvailableCommands = 0;
char *interfaceScreen[] = {     " ________   ___  ___   _______    ________    ________ ",
                                "|\\   ____\\ |\\  \\|\\  \\ |\\  ___ \\  |\\   ____\\  |\\   ____\\",
                                "\\ \\  \\___| \\ \\  \\\\\\  \\\\ \\   __/| \\ \\  \\___|_ \\ \\  \\___|_",
                                " \\ \\  \\     \\ \\   __  \\\\ \\  \\_|/__\\ \\_____  \\ \\ \\_____  \\",
                                "  \\ \\  \\____ \\ \\  \\ \\  \\\\ \\  \\_|\\ \\\\|____|\\  \\ \\|____|\\  \\",
                                "   \\ \\_______\\\\ \\__\\ \\__\\\\ \\_______\\ ____\\_\\  \\  ____\\_\\  \\",
                                "    \\|_______| \\|__|\\|__| \\|_______||\\_________\\|\\_________\\",
                                "                                    \\|_________|\\|_________|"};
int interfaceScreenSize = sizeof(interfaceScreen) / sizeof(char*);
char *gameOption[] ={   "Start a new Game",
                        "Continue",
                        "Help",
                        "Setting",
};
int gameOptionSize = sizeof(gameOption) / sizeof(char*);
char *errorCode[] = { "no input",
                    "large",
                    "number out of bound",
                    "letter out of bound",
                    "number out of list",
                    "not valid move",
                    "empty block",
                    "not command",
                    "no promotion",
                    "bad input",
                    "not one piece",
                    "move one piece"
};
char *errorMessage[] = {    "Please Make sure you entered a valid input.",
                            "The input you entered was Too large.",
                            "The Index number you entered was out of bound.",
                            "Make sure you type the right Character in uppercase.",
                            "Make sure the number you entered exists in the List.",
                            "The move you just entered is invalid.",
                            "The Block you entered is an empty one.",
                            "This command wasn't recognized",
                            "promotion isn't available in this move.\nPlease recheck your move.",
                            "Please make sure you entered the input in the correct structure.",
                            "You can only promote to one's own pieces.",
                            "You can only move your own's pieces."
};
int errorMessageSize = sizeof(errorCode) / sizeof(char*);

char commandSpecial[] = { 's', 'l', 'u', 'r', 'n', 'b'};
int commandSpecialSize = sizeof(commandSpecial) / sizeof(char);

char promotable[] = { 'r', 'n','q','b'};
int sizeOfPromotable = sizeof(promotable) / sizeof( promotable[0]);

char backupBoard[8][8];

bool hasBoard = false;
bool end = false;

void printInterface(void)
{
    printf("This is a Chess Game made by Team \"M&Ms\" as a project for Programming I course.\n");
    printGameOption();
}
void printLogo(void)
{
        setColor("RED");
        int INDEX;
        for( INDEX = 0; INDEX < interfaceScreenSize; INDEX++)
        {
            printf("%s\n",interfaceScreen[INDEX] );
        }
        setColor("DEFAULT");
}
void printGameOption(void)
{
        int INDEX;
        for( INDEX = 0; INDEX < gameOptionSize; INDEX++)
        {
            printf("%d- %s\n", INDEX+1, gameOption[INDEX]);
        }
}
void clearScreen(void)
{
        system("cls");
        return;
}
int getGameOption(void)
{
        char input[3];
        bool endFound = false, rightNum = false;
        do
        {
                endFound= false;
                rightNum = false;
                printf("Type the Number facing your desired Menu Option.\n");
                scanf("%s", input);
                if( input[1] == '\0')
                        endFound = true;
                if( (input[0] > '0') && (input[0] <= '0' + gameOptionSize) )
                        rightNum = true;
                if( (!endFound) )
                    printError("large");
                else if ( (!rightNum) )
                    printError("number not in list");
        }while( (!endFound) || (!rightNum));
        return input[0] - '0';
}

void getMove()
{
        commandStart = false;
        char input[7];
        bool done,promotion;
        do
        {
            done = false;
            promotion = false;
            printf("Enter the Index of current and Desired Move: ");
            scanf("%s",input);
            int nullPosition = getNull( input, 7);
            if( nullPosition == 1 )
            {
                if( verifyCommand(input[0]) )
                {
                    commandStart = true;
                    break;
                }else
                printError("not command");
            }
            else if( nullPosition == 4 || nullPosition == 5 )
            {
                switch( nullPosition){
                case 4:
                    promotion = false;
                    break;
                case 5:
                    promotion = true;//TODO
                    break;
                }
                if( verifyInput( input) )
                {
                    if( promotion)
                    {
                        if( checkPromotion( input) )
                        {
                            done = true;
                            promotion = true;
                        }
                        else
                        {
                            done = false;
                            promotion = false;
                        }
                    }else
                    {
                        done = true;
                    }
                }
            }else if( nullPosition == 0)
                printError("no input");
            else
                printError("bad input");
            setCommand( input, promotion);
        }while( !(done || commandStart) );
        if( commandStart )
        {
            doCommand( input[0]);
        }
        else
        {
            setCommand( input, promotion);
        }
}

bool verifyNumber(char number)
{
    if( (number > '0') && (number < '9') )
        return true;
    else
        return false;
}

bool verifyLetter(char letter)
{
    if( (letter >= 'A') && (letter <= 'H') )
        return true;
    else
        return false;
}

int getNull( char input[], int maxSize)
{
    int INDEX;
    for( INDEX = 0; INDEX < maxSize; INDEX++)
        if( input[INDEX] == '\0' )
            return INDEX;
    return 0;
}

int convertLetter( char letter)
{
    return (letter - 'A');
}

int convertNumber( char number)
{
    return ( 8 - (number - '1' + 1));
}
bool verifyInput( char input[])
{
    bool verifiedInput = true;
    if( verifyLetter( input[0]) && verifyLetter( input[2]) )
        verifiedInput = true;
    else
    {
        printError("letter out of bound");
        verifiedInput = false;
    }
    if( verifyNumber( input[1]) && verifyNumber( input[3]) )
        verifiedInput = true;
    else
    {
        printError("number out of bound");
        verifiedInput = false;
    }
    return verifiedInput;
}
void printError(char *type)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    int INDEX;
    for( INDEX = 0; INDEX < errorMessageSize; INDEX++)
    {
        if( strcmp(type, errorCode[INDEX]) == 0 )
        {
            printf("%s\n", errorMessage[INDEX]);
            break;
                }
        }
        printf("Please refer to the help section if you need more informations.\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);
}
void doCommand( char input)
{
    switch( input)
    {
    case 's':
        saveGame();
        break;
    case 'l':
        loadGame();
        break;
    case 'u':
        undo();
        break;
    case 'r':
        //redo();
        break;
    case 'n':
        resetBoard();
        break;
    case 'b':
        goBack();
        break;
    default:
        printError("no input");
    }
}

void setCommand( char input[], bool promotion)
{
    command.currentY = convertNumber( input[1]);
    command.currentX = convertLetter( input[0]);
    command.nextY = convertNumber( input[3]);
    command.nextX = convertLetter( input[2] );
    if( promotion)
    {
        command.promotion = input[4];
        command.promotionExist = true;
    }
    else
    {
        command.promotion = '\0';
        command.promotionExist = false;
    }
}

bool verifyCommand( char input)
{

    for(int counter = 0; counter < commandSpecialSize; counter++)
    {
        if( input == commandSpecial[counter])
            return true;
    }
    return false;
}

void printHelp()
{
    printLogo();
    printf("Hello This is the help Section: \n\
Game Play:\n\
-You can start either by New Game or Continue game if you want\n\
to continue a game you last played yet you didn\'t close the program.\n\
Make sure when moving Piece to enter it in the Form XYLM\n\
where :\n\
'A' <= X,L <= 'H'\n\
1 <= Y,M <= 8\n\
Make sure to capitalize the letters.\n\
If you want to promote a Pawn you can enter in this format XYLMT\n\
where T is the promoted to piece.\n\
make sure to Capitalize the Letters when needed.\n\
\n\
Commands:\n\
There are certain commands used in this game.\n\
'b' : used to go back to the main menu.\n\
'l' : used to load a past saved game.\n\
's' : used to save a game for later use.\n\
'u' : used to undo a move.\n\
'r' : used to redo a move.\n\
'n' : used to reset the board and start a new age.\n");
    printf("Type \'b\' to get back to the main menu: ");
    getchar();
    while( getchar() != 'b' )
    {
        printf("Not acceptable command.\nType \'b\' to get back to the main menu: ");
        getchar();
    }
    state = menu;
}

void setColor(char* text)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    if( strcmp(text,"RED") == 0)
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    else if( strcmp(text, "BLUE") == 0 )
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    else if( strcmp(text, "GREEN") == 0 )
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    else if( strcmp(text, "INTENSITY") == 0 )
        SetConsoleTextAttribute(hConsole,  FOREGROUND_INTENSITY);
    else if ( strcmp(text,"DEFAULT") == 0 )
        SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    else
        SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void setBackgroundColor(char* text)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    if( strcmp(text,"RED") == 0)
        SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
    else if( strcmp(text, "BLUE") == 0 )
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
    else if( strcmp(text, "GREEN") == 0 )
        SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    else if( strcmp(text, "INTENSITY") == 0 )
        SetConsoleTextAttribute(hConsole,  FOREGROUND_INTENSITY);
    else if ( strcmp(text,"DEFAULT") == 0 )
        SetConsoleTextAttribute(hConsole,  BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
    else
        SetConsoleTextAttribute(hConsole,  BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

void switchTurn()
{
    currentPlayer = !currentPlayer;
}

void gameFlow()
{
    printBoard();
    while(!end)
    {
        collectMove();
        simulation = true;
        if( isChecked() && sizeOfAvailableCommands == 0)
        {
            if( currentPlayer == firstPlayer)
                gameWin = secondPlayer;
            else
                gameWin = firstPlayer;
        }
        else if( sizeOfAvailableCommands == 0)
        {
            gameWin = draw;
        }
        else if ( isChecked() )
        {
            printf("Be ware that's a check.\n");
        }
        simulation = false;
        if( gameWin == none && applyMove() )
        {
            switchTurn();
            clearScreen();
            printBoard();
        }else if ( gameWin == none)
        {
            commandStart = false;
            clearScreen();
            printBoard();
            break;
        }
        if(gameWin != none)
        {
            if( gameWin == player1)
                printf("Player1 Win,CheckMate");
            else if ( gameWin == player2)
                printf("player2 Win,CheckMate");
            else
                printf("Draw,StaleMate");
            getchar();
            getchar();
            resetAll();
            clearScreen();
            printBoard();
        }
    }
}

void goBack()
{
    if( state == play || state == help || state == setting )
        state = menu;
}

void printRequiredScreen()
{
    switch (state)
    {
    case menu:
        startMenu();
        break;
    case help:
        printHelp();
        break;
    case setting:
        printSetting();
        break;
    case play:
        gameFlow();
        break;
    }
}
void startMenu()
{
    printLogo();
    printInterface();
    int temp =getGameOption();
    switch(temp)
    {
    case 1:
        resetAll();
        state = play;
        break;
    case 2:
        if( !hasBoard)
        {
            resetAll();
        }
        state = play;
        break;
    case 3:
        state = help;
        break;
    case 4:
        state = setting;
        break;
    }
}
void printSetting()
{
    //not finished
}

void game()
{
    hasBoard = false;
    while(1)
    {
        clearScreen();
        printRequiredScreen();
    }
}

bool checkPromotion( char input[])
{
    bool allowedToPromote = false;
    int currentY = convertNumber( input[1]);
    int currentX = convertLetter( input[0]);
    int nextY = convertNumber( input[3]);
    if( (board[currentY][currentX] == 'p' && currentY == 6 && nextY == 7 ) || (board[currentY][currentX] == 'P' && currentY == 1 && nextY == 0 ))
        allowedToPromote = true;
    if( (currentPlayer == firstPlayer && isupper( input[4]) ) || (currentPlayer == secondPlayer && islower( input[4] ) ) )
        allowedToPromote = true;
    else
    {
        printError("not one piece");
        allowedToPromote = false;
        return false;
    }
    if( allowedToPromote)
    {
        for(int INDEX = 0; INDEX < sizeOfPromotable; INDEX++)
        {
                if( tolower( input[4]) == promotable[INDEX] )
                    return true;
        }
    }
    printError("no promotion");
    return false;
}

void doPromotion()
{
    if( command.promotionExist)
    {
        board[command.nextY][command.nextX] = command.promotion;
        command.promotionExist = false;
        savePromotion();
    }

}

void resetAll()
{
    resetBoard();
    currentPlayer = firstPlayer;
    simulation = false;
    gameWin = none;
    hasBoard = true;
    graveyard1Size = 0;
    graveyard2Size = 0;
    numberOfDeadPieces = 0;
    promotionSize = 0;
    turn = 0;
}

void collectMove()
{
    char testCase[] = "A1A1";
    simulation = true;
    sizeOfAvailableCommands = 0;
    copyBoard( board, backupBoard);
    struct commands backup = command;
    while( strcmp( testCase, "H8H9") != 0 )
    {
        copyBoard( backupBoard, board);
        command.currentY = convertNumber( testCase[1]);
        command.currentX = convertLetter( testCase[0]);
        command.nextY = convertNumber( testCase[3]);
        command.nextX = convertLetter( testCase[2] );
        bool acceptedMove = false;
        int x1 = command.currentX ;
        int y1 = command.currentY ;
        int x2 = command.nextX;
        int y2 = command.nextY;
        if( checkRightPiece(x1,y1) )
            switch(board[command.currentY][command.currentX])
            {
                case 'P':
                case 'p':
                    acceptedMove = checkSoldier( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                    break;
                case 'R':
                case 'r':
                    acceptedMove = checkRook(  x1, y1, x2, y2, board[command.currentY][command.currentX]);
                    break;
                case 'N':
                case 'n':
                    acceptedMove = checkHorse( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                    break;
                case 'B':
                case 'b':
                    acceptedMove = checkBishop( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                    break;
                case 'Q':
                case 'q':
                    acceptedMove = checkQueen( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                    break;
                case 'K':
                case 'k':
                    acceptedMove = checkKing( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                    break;
            }
            if( acceptedMove && !isChecked() )
            {
                availableCommands[sizeOfAvailableCommands] = command;
                sizeOfAvailableCommands++;
            }
            increment( testCase);
    }
    copyBoard( backupBoard, board);
    command = backup;
    simulation = false;
}

void increment( char testCase[])
{
    if( strcmp( testCase, "H8H8") == 0)
        testCase[3]++;
    else if( testCase[3] == '8')
    {
        testCase[3] = '1';
        if( testCase[2] == 'H')
        {
            testCase[2] = 'A';
            if( testCase[1] == '9' )
            {
                testCase[1] = '1';
                testCase[0]++;
            }
            else
                testCase[1]++;
        }
        else
            testCase[2]++;
    }
    else
        testCase[3]++;
}

bool checkIfAvailable(struct commands command)
{
    for(int counter = 0; counter < sizeOfAvailableCommands; counter++)
    {
        if( checkStructs( command, availableCommands[counter]) )
            return true;
    }
    return false;
}

bool checkStructs( struct commands command, struct commands test)
{

    if( command.currentX == test.currentX)
        if( command.currentY == test.currentY)
            if(command.nextX == test.nextX )
                if(command.nextY == test.nextY)
                    return true;
    return false;
}

void copyBoard( char board[8][8], char simulationBoard[8][8])
{
    for(int counter=0; counter < 8; counter++)
    {
        for(int counter2=0; counter2 < 8 ;counter2++)
        {
            simulationBoard[counter][counter2] = board[counter][counter2];
        }
    }
}
