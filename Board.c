#include <stdio.h>
#include "Board.h"
#include "Game.h"

void printBoard(void)//prints the board
{
    int i,j;//loop counters
    setColor("CYAN");//sets the color to cyan
    for(i = 0 ; i < 8 ; i++)
    {
        printf("\t%c",'A' + i);//prints the horizontal coordinates of the board
        if(i == 7)
        {
            setColor("RED");//sets the color to red
            printf("\t**Graveyard**");//prints the word graveyard
            setColor("DEFAULT");//sets the color to white
        }
    }

    for(i = 0 ; i < 8 ; i++)
    {
        setColor("CYAN");//sets the color to cyan
        printf("\n\n\n%d",8 - i);//prints the horizontal coordinates of the board
        setColor("DEFAULT");//sets the color to white
        for(j = 0 ; j < 8 ; j++)
        {
            printf("\t%c",board[i][j]);//prints the pieces on the board row by row
        }

        printf("\t");//prints a tab
        setColor("RED");//sets the color to red
        if(2*i  < graveyard1Size)//checks if the piece exists in the graveyard
        {
            printf("%c",player1Graveyard[2*i]);//prints the pieces in player 1 graveyard

        }
        if(2*i + 1 < graveyard1Size)//checks if the piece exists in the graveyard
        {
            printf("  %c",player1Graveyard[2*i + 1]);//prints the pieces in player 1 graveyard
        }
        printf("\t  ");//prints a tab
        if(2*i < graveyard2Size)//checks if the piece exists in the graveyard
        {
            printf("%c",player2Graveyard[2*i]);//prints the pieces in player 2 graveyard
        }
        if(2*i + 1 < graveyard2Size)//checks if the piece exists in the graveyard
        {
            printf("  %c",player2Graveyard[2*i + 1]);//prints the pieces in player 2 graveyard
        }
        setColor("DEFAULT");//resets the color to white
    }
    printf("\n");//prints a new line
}

void resetBoard(void)//resets the board
{
    int i,j;//loop counters
    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            if(i > 1 && i < 6)
            {
                    if( (i + j) % 2 == 0 )//resets the empty spaces in the board
                            board[i][j] = '#';
                    else
                            board[i][j] = '-';
            }
            else if ( i == 6)//resets the Pawns
                    board[i][j] = 'P';
            else if ( i == 1)//resets the pawns
                    board[i][j] = 'p';
            else if(i == 7)
            {
                if(j == 0 || j == 7)//resets the Rook
                    board[i][j] = 'R';
                else if(j == 1 || j == 6)//resets the Knight
                    board[i][j] = 'N';
                else if(j == 2 || j == 5)//resets the Bishop
                    board[i][j] = 'B';
                else if(j == 3)//resets the Queen
                    board[i][j] = 'Q';
                else//resets the King
                    board[i][j] = 'K';
            }
            else
            {
                if(j == 0 || j == 7)
                    board[i][j] = 'r';//resets the rook
                else if(j == 1 || j == 6)//resets the knight
                    board[i][j] = 'n';
                else if(j == 2 || j == 5)//resets the bishop
                    board[i][j] = 'b';
                else if(j == 3)
                    board[i][j] = 'q';//resets the queen
                else//resets the king
                    board[i][j] = 'k';
            }

        }
    }
}
void addToDeadPieces()//adds the piece captured in a turn to the list of captured pieces this turn for undo and redo
{
    deadPieces[turn+1] = board[command.nextY][command.nextX];
}
void saveMove()//saves the move for undo and redo
{
    moves[turn-1][0] = command.currentX;
    moves[turn-1][1] = command.currentY;
    moves[turn-1][2] = command.nextX;
    moves[turn-1][3] = command.nextY;
}
void loadUndoMove()//loads the move (reversed) for undo
{
    command.currentY = moves[turn-1][3] ;
    command.currentX = moves[turn-1][2] ;
    command.nextY = moves[turn-1][1] ;
    command.nextX = moves[turn-1][0] ;
}
void loadRedoMove()//loads the move for redo
{
    command.currentX = moves[turn][0];
    command.currentY = moves[turn][1];
    command.nextX = moves[turn][2];
    command.nextY = moves[turn][3];
}
void savePromotion()//saves the promotion for undo and redo
{
    promotion[turn] = command.promotion;
}
