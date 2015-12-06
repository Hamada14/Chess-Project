#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Game.h"


void printInterface(void)
{
        printLogo();
        printf("This is a Chess Game made by Team \"M&Ms\" as a project for Programming I course.\n");
        printGameOption();
}
void printLogo(void)
{
        int INDEX;
        for( INDEX = 0; INDEX < interfaceScreenSize; INDEX++)
        {
                printf("%s\n",interfaceScreen[INDEX] );
        }
}
void printGameOption(void)
{
        int INDEX;
        for( INDEX = 0; INDEX < gameOptionSize; INDEX++)
        {
                printf("%d- %s\n", INDEX+1, gameOption[INDEX]);
        }
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
                scanf("%s", &input);
                if( input[1] == '\0')
                        endFound = true;
                if( (input[0] > '0') && (input[0] <= '0' + gameOptionSize) )
                        rightNum = true;
                if( (!endFound) )
                        printf(ANSI_COLOR_RED"Your input is too large.\nPlease only enter the Number of the Option.\n"ANSI_COLOR_RESET "\n");
                else if ( (!rightNum) )
                        printf(ANSI_COLOR_RED"This Number isn't included in the List.\n"ANSI_COLOR_RESET "\n");
        }while( (!endFound) || (!rightNum));
        return input[0] - '0';
}

int getMove(char *moveType)//Move type such as current place or next place"
{
        char input[4];
        bool endFound = false, rightForm = false;
        do
        {
                endFound= false;
                rightForm = false;
                if( strcmp (moveType,"current") == 0 )
                        printf("Enter the Current Coordinate of the piece you wish to Move: ");
                else if ( strcmp(moveType, "next") == 0 )
                        printf("Enter the Current Coordinate of the place you wish to Move to: ");
                scanf("%s", &input);
                if( input[2] == '\0')
                        endFound = true;
                if( (input[0] >= 'A' && input[0] <='H') && (input[1] > '0' && input[1] <= '8') )
                        rightForm = true;
                if( (!endFound) )
                        printf(ANSI_COLOR_RED"Your input is too large.\nPlease only enter The character of the Column in uppercase followed by\n the number of the Row without spaces.\n"ANSI_COLOR_RESET "\n");
                else if ( (!rightNum) )
                        printf(ANSI_COLOR_RED"Please only enter The character of the Column in uppercase followed by\n the number of the Row without spaces.\n"ANSI_COLOR_RESET "\n");
        }while( (!endFound) || (!rightNum));
        int point;
        point = ( input[0] - 'A' +1) + ( input[0] - '0')*8 ;
        return point;
}
