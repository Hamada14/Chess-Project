#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"
#include <stdlib.h>
#include "Board.h"
#include "Save.h"
#include "Movement.h"
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
                    "not command"
};
char *errorMessage[] = {    "Please Make sure you entered a valid input.",
                            "The input you entered was Too large.",
                            "The Index number you entered was out of bound.",
                            "Make sure you type the right Character in uppercase.",
                            "Make sure the number you entered exists in the List.",
                            "The move you just entered is invalid.",
                            "The Block you entered is an empty one.",
                            "This command wasn't recognized"
};
int errorMessageSize = sizeof(errorCode) / sizeof(char*);

char commandSpecial[] = { 's', 'l', 'u', 'r', 'n', 'b'};
int commandSpecialSize = sizeof(commandSpecial) / sizeof(char);

bool end = false;

void printInterface(void)
{
    printLogo();
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
        system("clear");
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
                    done = true;
                }
            }else if( nullPosition == 0)
                printError("no input");
            else
                printError("large");
        }while( !done );
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
        //call the undo function here
        break;
    case 'r':
        //call the redo function here
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

void printHelp()//TODO
{
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
        //check for checkmates and stale mate and winning
        if( !applyMove() );
        {
            commandStart = false;
            break;
        }
        clearScreen();
        switchTurn();
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
    if(temp == 1 )
    {
        resetBoard();
        state = play;
    }
    else if( temp == 2 )
        state = play;
    else if( temp == 3 )
        state = help;
    else if( temp == 4 )
        state = setting;
}
void printSetting()
{
    //not finished
}

void game()
{
    while(1)
    {
        printRequiredScreen();
    }
}
