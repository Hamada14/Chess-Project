#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Board.h"
#include "Game.h"
#include "Save.h"
#include "Movement.h"
void saveGame(void)
{
    FILE* save;
    save = fopen("save.bin","wb");
    if(save == NULL)
    {
        printf("ERROR: failed to open file");
        return;
    }
    fwrite(board,64,1,save);
    fwrite(&graveyard1Size,1,1,save);
    fwrite(player1Graveyard,graveyard1Size,1,save);
    fwrite(&graveyard2Size,1,1,save);
    fwrite(player2Graveyard,graveyard2Size,1,save);
    fwrite(&currentPlayer,1,1,save);
    fwrite(&turn,1,1,save);
    fclose(save);
}
void loadGame(void)
{
    FILE* load;
    load = fopen("save.bin","rb");
    if(load == NULL)
    {
        printf("ERROR: failed to open file");
        return;
    }
    fread(board,64,1,load);
    fread(&graveyard1Size,1,1,load);
    fread(player1Graveyard,graveyard1Size,1,load);
    fread(&graveyard2Size,1,1,load);
    fread(player2Graveyard,graveyard2Size,1,load);
    fread(&currentPlayer,1,1,load);
    fread(&turn,1,1,load);
    fclose(load);
    minTurn = turn;
    maxTurn = turn;
}
bool undo()
{
    if(turn <= minTurn)
    {
        printf("error! nothing to undo");
        return false;
    }
    else
    {
        currentPlayer = !currentPlayer ;
        if( gameWin != none)
            gameWin = none;
        loadUndoMove();
        movePiece();
        if(deadPieces[turn] != 0)
        {
            board[command.currentY][command.currentX] = deadPieces[turn];
            deadPiecesTemp[turn] = deadPieces[turn];
            if(isupper(deadPieces[turn]))
            {
                graveyard1Size--;
            }
            else
            {
                graveyard2Size--;
            }
            deadPieces[turn] = 0;
        }
        if(promotion[turn] != 0)
        {
            if(currentPlayer == firstPlayer)
            {
                board[command.nextY][command.nextX] = 'P';
            }
            else
            {
                board[command.nextY][command.nextX] = 'p';
            }
        }
        turn--;
        printBoard();
    }
    return true;
}
void redo()
{
    if(turn >= maxTurn || turn < minTurn)
    {
        printf("error! nothing to redo");
    }
    else
    {
        loadRedoMove();
        movePiece();
        if(promotion[turn+1] != 0 )
        {
            board[command.nextY][command.nextX] = promotion[turn+1];
        }
        if(deadPiecesTemp[turn+1] != 0)
        {
            if(isupper(deadPiecesTemp[turn+1]))
                graveyard1Size++;
            else
                graveyard2Size++;
        }
        deadPieces[turn+1] = deadPiecesTemp[turn+1];
        currentPlayer = !currentPlayer;
        turn++;
        printBoard();
    }
}
