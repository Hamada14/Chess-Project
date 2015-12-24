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
//Used to save all available commands during the current turn and their killValue
//killValue refers to the value of the piece you can eat using such move
struct commands availableCommands[1000];
int killValue[1000] = {0};
int sizeOfAvailableCommands = 0;
//Game Logo and using the size to print the logo line by line
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
//Game options to choose from in the menu
char *gameOption[] = {   "Start a new Game",
                         "Continue",
                         "Help",
                         "Setting"
                     };
int gameOptionSize = sizeof(gameOption) / sizeof(char*);
//Error messages and their codes respectively
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
//to add a new command add its shortcut here and it's function in doCommand()
char commandSpecial[] = { 's', 'l', 'u', 'r', 'n', 'b','q'};
int commandSpecialSize = sizeof(commandSpecial) / sizeof(char);
//pieces which the pawn can promote to
char promotable[] = { 'r', 'n','q','b'};
int sizeOfPromotable = sizeof(promotable) / sizeof( promotable[0]);
/*
hasBoard is used to identify whether there's an already board or not
to avoid using th continue option without having one.
end is used to end the game
*/
bool hasBoard = false;
bool end = false;
bool gameTerminate = false;

void printInterface(void)
{
    printf("This is a Chess Game made by Team \"M&Ms\" as a project for Programming I course.\n");
    printGameOption();
}
//prints the Logo line by line
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
//prints the game Options in the menu
void printGameOption(void)
{
    int INDEX;
    for( INDEX = 0; INDEX < gameOptionSize; INDEX++)
    {
        printf("%d- %s\n", INDEX+1, gameOption[INDEX]);
    }
}
//clear the screen,warning: not portable
//if you test the project on a non windows machine remember to change the function
void clearScreen(void)
{
    system("cls");
    return;
}
//gets the player choice whether to start a new game , open the help menu ....
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
        //checks for large input
        if( input[1] == '\0')
            endFound = true;
        if( (input[0] > '0') && (input[0] <= '0' + gameOptionSize) )
            rightNum = true;
        if( input[0] == 'q' && input[1] == '\0')//used to quit the whole program
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
        getComputerCommand();//if using the player vs Computer, it generates the computer move
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
            //Checks for the position of the end of the string
            int nullPosition = getNull( input, 7);
            switch( nullPosition)
            {
            case 0:
            case 6:
                //too large input
                invalidInput = true;
                clearScreen();
                printBoard();
                printError("large");
                break;
            case 1:
                if( verifyCommand(input[0]) )//checks if it's valid command
                {
                    commandStart = true;
                }
                else
                {
                    invalidInput = true;//recognize input as invalid
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
                //checks if there's a promotion or not and whether it's moving the right piece
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
        if( commandStart )//if the program took a command it executes it
        {
            doCommand( input[0]);
        }
        else//if it got a move it checks if it's available and execute it
        {
            setCommand( input, promotion);
        }
    }
}

void getComputerCommand()
{
    srand(time(NULL));
    int random = rand() % sizeOfAvailableCommands;//generate a random number less than the number of available moves
    int maxValue = -20;
    int maxIndex = 0;
    int minValue = 10;
    for(int counter = 0; counter < sizeOfAvailableCommands; counter++)
    {
        if( killValue[counter] > maxValue )//search for highest kill value in the available moves collected
        {
            maxValue = killValue[counter];
            maxIndex = counter;
        }
        if( killValue[counter] < minValue)
            minValue = killValue[counter];
    }
    if( maxValue == minValue)
    {
            maxIndex = random;
    }//if the highest kill value =0 which means that it doesn't eat any piece it uses a random move
    command = availableCommands[maxIndex];
    lastComputerCommand[1] = '8' - availableCommands[maxIndex].currentY;
    lastComputerCommand[0] = availableCommands[maxIndex].currentX + 'A';
    lastComputerCommand[3] = '8' - availableCommands[maxIndex].nextY;
    lastComputerCommand[2] = availableCommands[maxIndex].nextX + 'A';
    char piece = board[availableCommands[maxIndex].currentY][availableCommands[maxIndex].currentX];
    if( availableCommands[maxIndex].nextY == 7 && piece == 'P')
    {
        command.promotionExist = true;
        command.promotion = 'Q';//if the generated move tried to place the pawn at the end of the board it promotes it
        lastComputerCommand[4] = 'Q';
        lastComputerCommand[5] = '\0';
    }
    else if( availableCommands[maxIndex].nextY == 0 && piece == 'p')
    {
        command.promotionExist = true;
        command.promotion = 'q';//if the generated move tried to place the pawn at the end of the board it promotes it
        lastComputerCommand[4] = 'q';
        lastComputerCommand[5] = '\0';
    }
    lastComputerCommand[4] = '\0';
}

//checks if the number is in the right range
bool verifyNumber(char number)
{
    return ( (number > '0') && (number < '9') )?true:false;
}

//checks if the letter is in the right range
bool verifyLetter(char letter)
{
    return ( (letter >= 'A') && (letter <= 'H') )?true:false;
}

//return the index of the null terminator in an array of characters
int getNull( char input[], int maxSize)
{
    int INDEX;
    for( INDEX = 0; INDEX < maxSize; INDEX++)
        if( input[INDEX] == '\0' )
            return INDEX;
    return 0;
}

//converts the letter to a position in the array
int convertLetter( char letter)
{
    return (letter - 'A');
}

//converts the number to a position in the array
int convertNumber( char number)
{
    return ( 8 - (number - '1' + 1));
}
//checks if the input is valid or not
bool verifyInput( char input[])
{
    if( verifyLetter( input[0]) && verifyLetter( input[2]) && verifyNumber( input[1]) && verifyNumber( input[3]) )
        return true;
    else
        return false;
}
//prints error by using the error code
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
//executes commands
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
        if(computerState == off)//in case of player vs player it undo one move only
            undoErrorPrint = !undo();//if there was no move to undo prints an error
        else//calls undo twice if the game is player vs computer
        {
            undoErrorPrint = !undo();//in case of player vs computer it undo 2 moves
            undoErrorPrint = !undo();
        }
        break;
    case 'r':
        if(computerState == off)
            redo();
        else//calls redo twice if the game was a player vs computer game
        {
            redo();
            redo();
        }
        break;
    case 'n':
        resetAll();//In case of new game it resets everything
        break;
    case 'b':
        goBack();
        break;
    case 'q':
        gameTerminate = true;//to terminate the whole program
        break;
    default:
        printError("no input");
    }
}
//takes the input given by the user and set it to the struct
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
//verifies that the character is a command shortcut by using the array in the beginning
bool verifyCommand( char input)
{

    for(int counter = 0; counter < commandSpecialSize; counter++)
    {
        if( input == commandSpecial[counter])
            return true;
    }
    return false;
}
//prints the help section
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
//prints the setting section to change computer mode
void printSetting()
{
    printLogo();
    if( computerState == on )//prints the computer state
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
        computerState = !computerState;//changes the computer state
    goBack();//go back to the main menu
}
//changes the color of the text according to need
//used the windows.h documentation over internet
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
//switches turn each time a player does a move
void switchTurn()
{
    currentPlayer = !currentPlayer;
}

void gameFlow()//the flow of game
{
    printBoard();//prints the board
    while(!end)
    {
        if( undoErrorPrint)//if there's an undo warning prints an error message
        {
            printError("no undo");
            undoErrorPrint = false;
        }
        if( redoErrorPrint)//if there's an redo warning prints an error message
        {
            printError("no redo");
            redoErrorPrint = false;
        }
        collectMove();//collects all available moves in this turn
        simulation = true;//starts the simulation mode to check if the king of the current player is checked
        copyBoard( board,backupBoard);//copy the board to a backup board to remain unchanged
        if( graveyard1Size == 15 && graveyard2Size == 15)
            gameWin = draw;
        if( isChecked() )
        {
            if(sizeOfAvailableCommands == 0)
            {
                if( currentPlayer == firstPlayer)//if the king is checked and there's no available moves then the player whose turn is now lose
                    gameWin = secondPlayer;
                else
                    gameWin = firstPlayer;
            }
            if( sizeOfAvailableCommands != 0)
            {
                setColor("MAGENTA");
                printf("Be ware that's a check.\n");//if the player still has an available moves he's warned about the check state only
                setColor("DEFAULT");
            }
        }
        else if( sizeOfAvailableCommands == 0)//if he isn't checked but has no available move then it's stale
        {
            gameWin = draw;
        }
        copyBoard( backupBoard, board);//obtain the main state of the board from the backup
        simulation = false;//turns the simulation mode off to continue the game
        if( gameWin == none && applyMove() )//applyMove() function gets the input and executes it
        {
            switchTurn();
            clearScreen();
            printBoard();
            if( firstTurn)
                firstTurn = false;
        }
        else if ( gameWin == none)//if applyMove return false then it was a command not a move and we end it
        {
            commandStart = false;
            clearScreen();
            printBoard();
            break;
        }
        if(gameWin != none)//if the game ended we announce the new state whether a draw or a winner
        {
            setColor("GREEN");
            if( gameWin == player1)
                printf("Player1 Wins,CheckMate\n");
            else if ( gameWin == player2)
            {
                if( computerState == off)
                    printf("Player2 Wins,CheckMate\n");
                else
                    printf("Computer Wins,CheckMate\n");//if you are playing against computer and he wins

            }
            else
                printf("Draw,StaleMate\n");
            setColor("DEFAULT");
            char input[7];//then we check whether he wants to save the winning board or undo something
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
            clearScreen();//clear the screen and print the board after every move is done
            printBoard();
        }
    }
}
//it returns to an upper layer window
void goBack()
{
    if( state != menu )
        state = menu;
}
//it checks what layer to print
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
//it prints the main menu and asks the user for input
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
        if( !hasBoard)//if he chooses to continue and he has no games left from before the game is reseted
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
    hasBoard = false;//it sets that he has no game
    while(!gameTerminate)//an infinite loop where the game keeps going under the user enters quit
    {
        clearScreen();
        printRequiredScreen();
    }
}
//checks for the promotion
bool checkPromotion( char input[], bool promotion)
{
    int currentY = convertNumber( input[1]);
    int currentX = convertLetter( input[0]);
    int nextY = convertNumber( input[3]);
    char piece = board[currentY][currentX];
    if( !checkRightPiece(currentX,currentY))//if trying to move a piece not his own
        return false;
    if( !(promotion) && tolower(piece) != 'p')//if trying to move your piece and not promoting a non pawn
        return true;
    else if( (promotion) && tolower(piece) != 'p')//if trying to promote a non pawn
    {
        clearScreen();
        printBoard();
        printError("cannot promote piece");
        return false;
    }else if( tolower(piece) == 'p')//if the piece moved is a pawn
    {
        if(  (piece == 'p' && nextY == 7) || (piece == 'P' && nextY == 0) )
        {
            if( !(promotion) )//if trying to place a pawn at the end of the board without promotion
            {
                clearScreen();
                printBoard();
                printError("must have promotion");
                return false;
            }
            if( (promotion) )
            {
                if( !(currentPlayer ^ isupper(input[4])) )//if trying to promote to the players piece
                {
                    clearScreen();
                    printBoard();
                    printError("not one piece");
                    return false;
                }
                for(int INDEX = 0; INDEX < sizeOfPromotable; INDEX++)
                {
                    if( tolower( input[4]) == promotable[INDEX] )//checks if promoting to a piece your promote to
                        return true;
                }
                clearScreen();
                printBoard();
                printError("no promotion");
                return false;
            }
        }else if( !(promotion) )
            return true;
        else if( (promotion))//if trying to promote before reaching the end of the board
        {
            clearScreen();
            printBoard();
            printError("cannot promote here");
        }
    }
    return false;
}
//does the promotion
void doPromotion()
{
    if( command.promotionExist)
    {
        board[command.nextY][command.nextX] = command.promotion;//promotes the piece
        command.promotionExist = false;
        savePromotion();//saves the promotion for undo and redo
    }
    else
    {
        promotion[turn] = 0;//resets the promotion list for undo and redo if no promotion was made this turn
    }

}
//reset all the stats to use in the start of game or when loading a file
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
//collect all available moves in a turn
void collectMove()
{
    char testCase[] = "A1A1";//starts by the first move A1A1 where it increment
    simulation = true;//starts simulation move
    sizeOfAvailableCommands = 0;//initialize the number of moves to zero
    copyBoard( board, backupBoard);//copy a backup of the main board
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
        int valueOfKill = checkValue( x2, y2);//if the move will kill a piece it return the value of the piece
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
        if( acceptedMove && !isChecked() )//if the move can be done and doesn't result a check it's available
        {
            availableCommands[sizeOfAvailableCommands] = command;
            killValue[sizeOfAvailableCommands] = valueOfKill;
            switchTurn();
            if( isChecked() )
                killValue[sizeOfAvailableCommands] += 3;//if the move will result in an opposite check then the computer does it
            int temp = checkValue(x2,y2);
            if( checkCanBeKilled(x2,y2,board))
            {
                killValue[sizeOfAvailableCommands] -= temp;//Subtracts the value of the piece itself if it can be killed
            }
            sizeOfAvailableCommands++;
            switchTurn();
        }
        increment( testCase);//increment the test case for example from A1A1 to A1A2
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
//checks if the command given by user is found in the available commands
bool checkIfAvailable(struct commands command)
{
    for(int counter = 0; counter < sizeOfAvailableCommands; counter++)
    {
        if( checkStructs( command, availableCommands[counter]) )
            return true;
    }
    return false;
}
//check if 2 structs are the same in some of their attributes
bool checkStructs( struct commands command, struct commands test)
{

    if( command.currentX == test.currentX)
        if( command.currentY == test.currentY)
            if(command.nextX == test.nextX )
                if(command.nextY == test.nextY)
                    return true;
    return false;
}
//function which copy the main board to a backup board
void copyBoard( char board[8][8], char simulationBoard[8][8])
{
    for(int counter=0; counter < 8; counter++)
    {
        for(int counter2=0; counter2 < 8 ; counter2++)
        {
            simulationBoard[counter][counter2] = board[counter][counter2];
        }
    }
}
//returns the value of a piece
int checkValue( int nextX, int nextY)
{
    if( !isalpha(board[nextY][nextX]))
        return 0;
    char type = tolower( board[nextY][nextX]);
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
//checks if a piece can be killed
bool checkCanBeKilled( int x2, int y2, char board[8][8])//check if the piece moved in the simulation will get killed
{
    char backupBoard[8][8];
    copyBoard(board,backupBoard);
    for(int counter = 0; counter < 8; counter++)
    {
        for(int counter2 = 0; counter2 < 8; counter2++)//iterates over the board to check if their a piece that can kill it
        {
            command.currentY = counter;
            command.currentX = counter2;
            command.nextY = y2;//it's set to the computer's piece's y-coordinate
            command.nextX = x2;//it's set to the computer's piece's x-coordinate
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
                if(acceptedMove)// if the move is accepted and this piece can move and eat the computer piece
                    return true;
                copyBoard(backupBoard,board);//reset the board
        }
    }
    return false;
}
