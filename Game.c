#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"
#include <stdlib.h>
#include "Board.h"
#include "Save.h"
#include "Movement.h"
#include <ctype.h>
#include <time.h>
int depth = 0;
struct commands availableCommands[1000];
int killValue[1000] = {0};
int sizeOfAvailableCommands = 0;

char *interfaceScreen[] = {     " ________   ___  ___   _______    ________    ________ ",
                                "|\\   ____\\ |\\  \\|\\  \\ |\\  ___ \\  |\\   ____\\  |\\   ____\\",
                                "\\ \\  \\___| \\ \\  \\\\\\  \\\\ \\   __/| \\ \\  \\___|_ \\ \\  \\___|_",
                                " \\ \\  \\     \\ \\   __  \\\\ \\  \\_|/__\\ \\_____  \\ \\ \\_____  \\",
                                "  \\ \\\\____ \\ \\  \\ \\  \\\\ \\  \\_|\\ \\\\|____|\\  \\ \\|____|\\  \\",
                                "   \\ \\_______\\\\ \\__\\ \\__\\\\ \\_______\\ ____\\_\\  \\  ____\\_\\  \\",
                                "    \\|_______| \\|__|\\|__| \\|_______||\\_________\\|\\_________\\",
                                "                                    \\|_________|\\|_________|"
                          };
int interfaceScreenSize = sizeof(interfaceScreen) / sizeof(char*);

char *gameOption[] = {   "Start a new Game",
                         "Continue",
                         "Help",
                         "Setting"
                     };
int gameOptionSize = sizeof(gameOption) / sizeof(char*);

char *errorCode[] = { "no input",
                      "large",
                      "number out of list",
                      "not valid move",
                      "empty block",
                      "not command",
                      "no promotion",
                      "bad input",
                      "not one piece",
                      "move one piece",
                      "king check",
                      "no undo",
                      "no redo",
                      "must have promotion",
                      "cannot promote piece",
                      "cannot promote here",
                      "promote one piece"
                    };
char *errorMessage[] = {    "Please Make sure you entered a valid input.",
                            "The input you entered was Too large.",
                            "Make sure the number you entered exists in the List.",
                            "The move you just entered is invalid.",
                            "The Block you entered is an empty one.",
                            "This command wasn't recognized",
                            "promotion isn't available in this move.\nPlease recheck your move.",
                            "Please make sure you entered the input in the correct structure.",
                            "You can only promote to one's own pieces.",
                            "You can only move your own's pieces.",
                            "You can't do such move in this situation.",
                            "There's nothing to undo at this stage of the game.",
                            "There's nothing to redo at this stage of the game.",
                            "You must promote when using this move.",
                            "You can only promote the pawn.",
                            "You can't promote here.",
                       };
int errorMessageSize = sizeof(errorCode) / sizeof(char*);

char commandSpecial[] = { 's', 'l', 'u', 'r', 'n', 'b','q'};
int commandSpecialSize = sizeof(commandSpecial) / sizeof(char);

char promotable[] = { 'r', 'n','q','b'};
int sizeOfPromotable = sizeof(promotable) / sizeof( promotable[0]);

bool hasBoard = false;
bool end = false;
bool gameTerminate = false;

void printInterface(void)
{
    printf("This is a Chess Game made by Team \"M&Ms\" as a project for Programming I course.\n");
    printGameOption();
}

void printLogo(void)
{
    setColor("GREEN");
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
        if( input[0] == 'q' && input[1] == '\0')
        {
            gameTerminate = true;
            break;
        }
        if( (!endFound) )
        {
            clearScreen();
            printLogo();
            printInterface();
            printError("large");
        }
        else if ( (!rightNum) )
        {
            clearScreen();
            printLogo();
            printInterface();
            printError("number out of list");
        }
    }
    while( (!endFound) || (!rightNum));
    return input[0] - '0';
}

void getMove()
{
    commandStart = false;
    char input[7];
    bool done,promotion;
    if( currentPlayer == secondPlayer && computerState == on)
    {
        getComputerCommand();
    }
    else
    {
        do
        {
            if( !firstTurn && computerState == on && currentPlayer == firstPlayer)
            {
                printf("The computer's last Command was %s.\n", lastComputerCommand);
            }
            done = false;
            promotion = false;
            bool invalidInput = false;
            setColor("GREEN");
            printf("Enter the Index of current and Desired Move: ");
            setColor("DEFAULT");
            scanf("%s",input);
            int nullPosition = getNull( input, 7);
            switch( nullPosition)
            {
            case 0:
            case 6:
                invalidInput = true;
                clearScreen();
                printBoard();
                printError("large");
                break;
            case 1:
                if( verifyCommand(input[0]) )
                {
                    commandStart = true;
                }
                else
                {
                    invalidInput = true;
                    clearScreen();
                    printBoard();
                    printError("not command");
                }
                break;
            case 2:
            case 3:
                invalidInput = true;
                clearScreen();
                printBoard();
                printError("bad input");
                break;
            case 4:
                promotion = false;
                break;
            case 5:
                promotion = true;
                break;
            }
            if( invalidInput)
                continue;
            if( commandStart)
                continue;
            if(  verifyInput( input))
            {
                done = true;
                if( !checkPromotion(input, promotion) )
                        done = false;
            }
            else
            {
                clearScreen();
                printBoard();
                printError("bad input");
            }
        }
        while( !(done || commandStart) );
        if( commandStart )
        {
            doCommand( input[0]);
        }
        else
        {
            setCommand( input, promotion);
        }
    }
}

void getComputerCommand()
{
    srand(time(NULL));
    int random = rand() % sizeOfAvailableCommands;
    int maxValue = -20;
    int maxIndex = 0;
    for(int counter = 0; counter < sizeOfAvailableCommands; counter++)
    {
        if( killValue[counter] > maxValue )
        {
            maxValue = killValue[counter];
            maxIndex = counter;
        }
    }
    if( maxValue == 0)
    {
            maxIndex = random;
    }
    command = availableCommands[maxIndex];
    lastComputerCommand[1] = '8' - availableCommands[maxIndex].currentY;
    lastComputerCommand[0] = availableCommands[maxIndex].currentX + 'A';
    lastComputerCommand[3] = '8' - availableCommands[maxIndex].nextY;
    lastComputerCommand[2] = availableCommands[maxIndex].nextX + 'A';
    char piece = board[availableCommands[maxIndex].currentY][availableCommands[maxIndex].currentX];
    if( availableCommands[maxIndex].nextY == 7 && piece == 'P')
    {
        command.promotionExist = true;
        command.promotion = 'Q';
        lastComputerCommand[4] = 'Q';
        lastComputerCommand[5] = '\0';
    }
    else if( availableCommands[maxIndex].nextY == 0 && piece == 'p')
    {
        command.promotionExist = true;
        command.promotion = 'q';
        lastComputerCommand[4] = 'q';
        lastComputerCommand[5] = '\0';
    }
    lastComputerCommand[4] = '\0';
}

bool verifyNumber(char number)
{
    return ( (number > '0') && (number < '9') )?true:false;
}

bool verifyLetter(char letter)
{
    return ( (letter >= 'A') && (letter <= 'H') )?true:false;
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
    if( verifyLetter( input[0]) && verifyLetter( input[2]) && verifyNumber( input[1]) && verifyNumber( input[3]) )
        return true;
    else
        return false;
}

void printError(char *type)
{
    setColor("RED");
    int INDEX;
    for( INDEX = 0; INDEX < errorMessageSize; INDEX++)
    {
        if( strcmp(type, errorCode[INDEX]) == 0 )
        {
            if( INDEX == 10 )
                setColor("MAGENTA");
            printf("%s\n", errorMessage[INDEX]);
            break;
        }
    }
    printf("Please refer to the help section if you need more informations.\n");
    setColor("DEFAULT");
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
        if(computerState == off)
            undoErrorPrint = !undo();
        else
        {
            undoErrorPrint = !undo();
            undoErrorPrint = !undo();
        }
        break;
    case 'r':
        if(computerState == off)
            redo();
        else
        {
            redo();
            redo();
        }
        break;
    case 'n':
        resetAll();
        break;
    case 'b':
        goBack();
        break;
    case 'q':
        gameTerminate = true;
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
    char x= 0;
    do
    {
        clearScreen();
        fflush(stdin);//flushes input to remove any unneeded input
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
        setColor("RED");
        if( x!= 0 && x!= 'b')
            printf("Not recognized as a command.\n");
        setColor("Default");
        printf("Type \'b\' to get back to the main menu: ");
        x = getchar();

    }
    while( x != 'b' );
    state = menu;
}

void printSetting()
{
    printLogo();
    if( computerState == on )
        printf("The computer mode is turned on.\n");
    else
        printf("The computer mode is turned off.\n");
    printf("Type \'b\' to get back to the main menu.\nType 1 to change Computer State: ");
    fflush(stdin);
    char x = getchar();
    while( x != 'b' && x!= '1')
    {
        printf("Not acceptable command.\nType \'b\' to get back to the main menu: ");
        fflush(stdin);
        x = getchar();
    }
    if( x == '1' )
        computerState = !computerState;
    goBack();
}

void setColor(char* text)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    if( strcmp(text,"RED") == 0)
        SetConsoleTextAttribute(hConsole, 12);
    else if( strcmp(text, "CYAN") == 0 )
        SetConsoleTextAttribute(hConsole, 11);
    else if( strcmp(text, "MAGENTA") == 0 )
        SetConsoleTextAttribute(hConsole, 13);
    else if( strcmp(text, "GREEN") == 0 )
        SetConsoleTextAttribute(hConsole, 10);
    else if( strcmp(text, "INTENSITY") == 0 )
        SetConsoleTextAttribute(hConsole,  FOREGROUND_INTENSITY);
    else if ( strcmp(text,"DEFAULT") == 0 )
        SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    else
        SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
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
        if( undoErrorPrint)
        {
            printError("no undo");
            undoErrorPrint = false;
        }
        if( redoErrorPrint)
        {
            printError("no redo");
            redoErrorPrint = false;
        }
        collectMove();
        simulation = true;
        copyFromToBoard( board,backupBoard);
        if( graveyard1Size == 15 && graveyard2Size == 15)
            gameWin = draw;
        if( isChecked(board) )
        {
            if(sizeOfAvailableCommands == 0)
            {
                if( currentPlayer == firstPlayer)
                    gameWin = secondPlayer;
                else
                    gameWin = firstPlayer;
            }
            if( sizeOfAvailableCommands != 0)
            {
                setColor("MAGENTA");
                printf("Be ware that's a check.\n");
                setColor("DEFAULT");
            }
        }
        else if( sizeOfAvailableCommands == 0)
        {
            gameWin = draw;
        }
        copyFromToBoard( backupBoard, board);
        simulation = false;
        if( gameWin == none && applyMove() )
        {
            switchTurn();
            clearScreen();
            printBoard();
            if( firstTurn)
                firstTurn = false;
        }
        else if ( gameWin == none)
        {
            commandStart = false;
            clearScreen();
            printBoard();
            break;
        }
        if(gameWin != none)
        {
            setColor("GREEN");
            if( gameWin == player1)
                printf("Player1 Wins,CheckMate\n");
            else if ( gameWin == player2)
            {
                if( computerState == off)
                    printf("Player2 Wins,CheckMate\n");
                else
                    printf("Computer Wins,CheckMate\n");

            }
            else
                printf("Draw,StaleMate\n");
            setColor("DEFAULT");
            char input[7];
            do
            {
                printf("Enter a command: ");
                scanf(" %s",input);
                int nullPosition = getNull( input, 7);
                if( nullPosition == 1 )
                {
                    if( verifyCommand(input[0]) )
                    {
                        commandStart = true;
                        break;
                    }
                    else
                        printError("not command");
                }
                else if( nullPosition == 0)
                    printError("no input");
                else
                    printError("bad input");
            }
            while( !commandStart);
            if( commandStart )
            {
                doCommand( input[0]);
                commandStart = false;
            }
            clearScreen();
            printBoard();
        }
    }
}

void goBack()
{
    if( state != menu )
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
    case play:
        gameFlow();
        break;
    case setting:
        printSetting();
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

void game()
{
    hasBoard = false;
    while(!gameTerminate)
    {
        clearScreen();
        printRequiredScreen();
    }
}

bool checkPromotion( char input[], bool promotion)
{
    int currentY = convertNumber( input[1]);
    int currentX = convertLetter( input[0]);
    int nextY = convertNumber( input[3]);
    char piece = board[currentY][currentX];
    if( !checkRightPiece(piece))
        return false;
    if( !(promotion) && tolower(piece) != 'p')
        return true;
    else if( (promotion) && tolower(piece) != 'p')
    {
        clearScreen();
        printBoard();
        printError("cannot promote piece");
        return false;
    }else if( tolower(piece) == 'p')
    {
        if(  (piece == 'p' && nextY == 7) || (piece == 'P' && nextY == 0) )
        {
            if( !(promotion) )
            {
                clearScreen();
                printBoard();
                printError("must have promotion");
                return false;
            }
            if( (promotion) )
            {
                if( !(currentPlayer ^ isupper(input[4])) )
                {
                    clearScreen();
                    printBoard();
                    printError("not one piece");
                    return false;
                }
                for(int INDEX = 0; INDEX < sizeOfPromotable; INDEX++)
                {
                    if( tolower( input[4]) == promotable[INDEX] )
                        return true;
                }
                clearScreen();
                printBoard();
                printError("no promotion");
                return false;
            }
        }else if( !(promotion) )
            return true;
        else if( (promotion))
        {
            clearScreen();
            printBoard();
            printError("cannot promote here");
        }
    }
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
    else
    {
        promotion[turn] = 0;
    }

}

void resetAll()
{
    resetBoard();
    currentPlayer = firstPlayer;
    firstTurn = true;
    simulation = false;
    gameWin = none;
    hasBoard = true;
    graveyard1Size = 0;
    graveyard2Size = 0;
    turn = 0,maxTurn = 0;
}

void collectMove()
{
    char testCase[] = "A1A1";
    simulation = true;
    sizeOfAvailableCommands = 0;
    char backupBoard[8][8];
    copyFromToBoard( board, backupBoard);
    struct commands command;
    while( strcmp( testCase, "H8H9") != 0 )
    {
        copyFromToBoard( backupBoard, board);
        command.currentY = convertNumber( testCase[1]);
        command.currentX = convertLetter( testCase[0]);
        command.nextY = convertNumber( testCase[3]);
        command.nextX = convertLetter( testCase[2] );
        bool acceptedMove = false;
        int pieceValue = checkValue( board[command.currentY][command.currentX]);
        int opponentValue = checkValue( board[command.nextY][command.nextX]);
        switchTurn();
        bool beforeKilled = checkCanBeKilled(command.currentX, command.currentY, board);
        switchTurn();
        if( checkRightPiece(board[command.currentY][command.currentX]) )
            switch(board[command.currentY][command.currentX])
            {
            case 'P':
            case 'p':
                acceptedMove = checkSoldier(command,board, board[command.currentY][command.currentX]);
                break;
            case 'R':
            case 'r':
                acceptedMove = checkRook(command,board, board[command.currentY][command.currentX]);
                break;
            case 'N':
            case 'n':
                acceptedMove = checkHorse(command,board, board[command.currentY][command.currentX]);
                break;
            case 'B':
            case 'b':
                acceptedMove = checkBishop(command, board, board[command.currentY][command.currentX]);
                break;
            case 'Q':
            case 'q':
                acceptedMove = checkQueen(command, board, board[command.currentY][command.currentX]);
                break;
            case 'K':
            case 'k':
                acceptedMove = checkKing(command, board, board[command.currentY][command.currentX]);
                break;
            }
        if( acceptedMove && !isChecked(board))
        {
            availableCommands[sizeOfAvailableCommands] = command;
            killValue[sizeOfAvailableCommands] = opponentValue;
            if(beforeKilled)
                killValue[sizeOfAvailableCommands] += pieceValue;
            switchTurn();
            bool afterKilled = checkCanBeKilled(command.nextX,command.nextY,board);
            if( afterKilled)
                killValue[sizeOfAvailableCommands] -= pieceValue;
             if( isChecked(board) )
                killValue[sizeOfAvailableCommands] += 3;
            int val = rev(board);
            killValue[sizeOfAvailableCommands] -= val;
            switchTurn();
            //printf("%s beforeKilled:%d  afterKilled:%d killing:%d  rec:%d\n",testCase,beforeKilled,afterKilled,opponentValue,val);
            sizeOfAvailableCommands++;
        }
        increment( testCase);
    }
    copyFromToBoard( backupBoard, board);
    simulation = false;
}

int rev(char board[8][8])
{
    int sum = 0;
    if(depth == 2)
    {
        return 0;
    }
    char testCase[] = "A1A1";
    char lboard[8][8];
    copyFromToBoard( board, lboard);
    struct commands command;
    while( strcmp( testCase, "H8H9") != 0 )
    {
        copyFromToBoard( lboard, board);
        command.currentY = convertNumber( testCase[1]);
        command.currentX = convertLetter( testCase[0]);
        command.nextY = convertNumber( testCase[3]);
        command.nextX = convertLetter( testCase[2] );
        bool acceptedMove = false;
        int pieceValue = checkValue( board[command.currentY][command.currentX]);
        int opponentValue = checkValue( board[command.nextY][command.nextX]);
        switchTurn();
        bool beforeKilled = checkCanBeKilled(command.currentX, command.currentY, board);
        switchTurn();
        if( checkRightPiece(board[command.currentY][command.currentX]) )
            switch(board[command.currentY][command.currentX])
            {
            case 'P':
            case 'p':
                acceptedMove = checkSoldier(command,board, board[command.currentY][command.currentX]);
                break;
            case 'R':
            case 'r':
                acceptedMove = checkRook(command,board, board[command.currentY][command.currentX]);
                break;
            case 'N':
            case 'n':
                acceptedMove = checkHorse(command,board, board[command.currentY][command.currentX]);
                break;
            case 'B':
            case 'b':
                acceptedMove = checkBishop(command, board, board[command.currentY][command.currentX]);
                break;
            case 'Q':
            case 'q':
                acceptedMove = checkQueen(command, board, board[command.currentY][command.currentX]);
                break;
            case 'K':
            case 'k':
                acceptedMove = checkKing(command, board, board[command.currentY][command.currentX]);
                break;
            }
        if( acceptedMove && !isChecked(board))
        {
            sum = opponentValue;
            if(beforeKilled)
                sum += pieceValue;
            switchTurn();
            bool afterKilled = checkCanBeKilled(command.nextX,command.nextY,board);
            if( afterKilled)
                sum -= pieceValue;
             if( isChecked(board) )
                sum += 3;
            depth++;
            sum -= rev(board);
            depth--;
            switchTurn();
        }
        increment( testCase);
    }
    return sum;
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
            if( testCase[1] == '8' )
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

void copyFromToBoard( char board[8][8], char simulationBoard[8][8])
{
    for(int counter=0; counter < 8; counter++)
    {
        for(int counter2=0; counter2 < 8 ; counter2++)
        {
            simulationBoard[counter][counter2] = board[counter][counter2];
        }
    }
}

int checkValue(char type)
{
    if( !isalpha(type))
        return 0;
    type = tolower(type);
    switch(type)
    {
    case 'p':
        return 1;
        break;
    case 'r':
        return 2;
        break;
    case 'b':
        return 3;
        break;
    case 'n':
        return 4;
        break;
    case 'k':
        return 5;
        break;
    }
    return 0;
}

bool checkCanBeKilled( int x2, int y2, char lastBoard[8][8])
{
    char board[8][8];
    copyFromToBoard(lastBoard,board);
    for(int counter = 0; counter < 8; counter++)
    {
        for(int counter2 = 0; counter2 < 8; counter2++)
        {
            command.currentY = counter;
            command.currentX = counter2;
            command.nextY = y2;
            command.nextX = x2;
            bool acceptedMove = false;
            if( checkRightPiece(board[command.currentY][command.currentX]) )
                switch(board[command.currentY][command.currentX])
                {
                case 'P':
                case 'p':
                    acceptedMove = checkSoldier(command, board, board[command.currentY][command.currentX]);
                    break;
                case 'R':
                case 'r':
                    acceptedMove = checkRook(command, board, board[command.currentY][command.currentX]);
                    break;
                case 'N':
                case 'n':
                    acceptedMove = checkHorse(command, board, board[command.currentY][command.currentX]);
                    break;
                case 'B':
                case 'b':
                    acceptedMove = checkBishop(command, board, board[command.currentY][command.currentX]);
                    break;
                case 'Q':
                case 'q':
                    acceptedMove = checkQueen(command, board, board[command.currentY][command.currentX]);
                    break;
                case 'K':
                case 'k':
                    acceptedMove = checkKing(command, board, board[command.currentY][command.currentX]);
                    break;
                }
                if(acceptedMove)
                {
                    return true;
                }
        }
    }
    return false;
}
