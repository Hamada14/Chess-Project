#include <stdio.h>
#include "Game.h"


void printInterface(void)
{
        int INDEX;
        for( INDEX = 0; INDEX < interfaceScreenSize; INDEX++)
        {
                printf("%s\n",interfaceScreen[INDEX] );
        }
        printf("This is a Chess Game made by Team \"M&Ms\" as a project for Programming I course.\n");
        printf("Type the Number facing your desired Menu Option.\n");
        for( INDEX = 0; INDEX < gameOptionSize; INDEX++)
        {
                printf("%d- %s\n", INDEX+1, gameOption[INDEX]);
        }
}

int getGameOption(void)
{

}
