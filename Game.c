#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"
#include <stdlib.h>
#include "Board.h"
#include "Save.h"

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
        char input[2];
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
        char input[7];
        bool done,promotion,command;
        do
        {
            done = false;
            promotion = false;
            command = false;
            printf("Enter the Index of current and Desired Move: ");
            scanf("%s",input);
            int nullPosition = getNull( input, 7);
            if( nullPosition == 1)
            {
                if( verifyCommand( input[0]) )
                {
                    command = true;
                    break;
                }
            }
            if( nullPosition == 4 || nullPosition == 5 )
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
        if( command )
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
            printf("%s", errorMessage[INDEX]);
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
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
     saved_attributes = consoleInfo.wAttributes;
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
