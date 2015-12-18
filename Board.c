#include <stdio.h>
#include "Board.h"
#include "Game.h"

void printBoard(void)
{
    int i,j;
    setColor("CYAN");
    for(i = 0 ; i < 8 ; i++)
    {
        printf("\t%c",'A' + i);
        if(i == 7)
        {
            setColor("RED");
            printf("\t**Graveyard**");
            setColor("DEFAULT");
        }
    }

    for(i = 0 ; i < 8 ; i++)
    {
        setColor("CYAN");
        printf("\n\n\n%d",8 - i);
        setColor("DEFAULT");
        for(j = 0 ; j < 8 ; j++)
        {
           printf("\t%c",board[i][j]);
        }

        printf("\t");
        setColor("RED");
        if(2*i  < graveyard1Size)
        {
            printf("%c",player1Graveyard[2*i]);
        }
        if(2*i + 1 < graveyard1Size)
        {
            printf("  %c",player1Graveyard[2*i + 1]);
        }
        printf("\t  ");
        if(2*i < graveyard2Size)
        {
            printf("%c",player2Graveyard[2*i]);
        }
        if(2*i + 1 < graveyard2Size)
        {
            printf("  %c",player2Graveyard[2*i + 1]);
        }
        setColor("DEFAULT");
    }
    printf("\n");
}

void resetBoard(void)
{
    int i,j;
    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            if(i > 1 && i < 6)
            {
                    if( (i + j) % 2 == 0 )
                            board[i][j] = '#';
                    else
                            board[i][j] = '-';
            }
            else if ( i == 6)
                    board[i][j] = 'P';
            else if ( i == 1)
                    board[i][j] = 'p';
            else if(i == 7)
            {
                if(j == 0 || j == 7)
                    board[i][j] = 'R';
                else if(j == 1 || j == 6)
                    board[i][j] = 'N';
                else if(j == 2 || j == 5)
                    board[i][j] = 'B';
                else if(j == 3)
                    board[i][j] = 'Q';
                else
                    board[i][j] = 'K';
            }
            else
            {
                if(j == 0 || j == 7)
                    board[i][j] = 'r';
                else if(j == 1 || j == 6)
                    board[i][j] = 'n';
                else if(j == 2 || j == 5)
                    board[i][j] = 'b';
                else if(j == 3)
                    board[i][j] = 'q';
                else
                    board[i][j] = 'k';
            }

        }
    }
}
void addToDeadPieces()
{
    deadPieces[turn+1] = board[command.nextY][command.nextX];
}
void saveMove()
{
    moves[turn-1][0] = command.currentX;
    moves[turn-1][1] = command.currentY;
    moves[turn-1][2] = command.nextX;
    moves[turn-1][3] = command.nextY;
}
void loadUndoMove()
{
    command.currentY = moves[turn-1][3] ;
    command.currentX = moves[turn-1][2] ;
    command.nextY = moves[turn-1][1] ;
    command.nextX = moves[turn-1][0] ;
}
void loadRedoMove()
{
    command.currentX = moves[turn][0];
    command.currentY = moves[turn][1];
    command.nextX = moves[turn][2];
    command.nextY = moves[turn][3];
}
void savePromotion()
{
    promotion[turn] = command.promotion;
}
