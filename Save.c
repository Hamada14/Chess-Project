#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Board.h"
#include "Game.h"
#include "Save.h"
#include "Movement.h"
void saveGame(void)//saves the game
{
    FILE* save;
    save = fopen("save.bin","wb");//opens the file for writing binary data
    if(save == NULL)//checks if the file was opened successfully
    {
        printf("ERROR: failed to open file");
        return;
    }
    fwrite(board,64,1,save);//writes the board in ascii mode
    fwrite(&graveyard1Size,1,1,save);//writes the size of graveyard 1 in binary mode
    fwrite(player1Graveyard,graveyard1Size,1,save);//writes graveyard 1 in ascii mode
    fwrite(&graveyard2Size,1,1,save);//writes the size of graveyard 2 in binary mode
    fwrite(player2Graveyard,graveyard2Size,1,save);//writes graveyard 2 in ascii mode
    fwrite(&currentPlayer,1,1,save);//writes the current player
    fclose(save);//closes the file
}
void loadGame(void)//the function that loads the game
{
    FILE* load;
    load = fopen("save.bin","rb");//opens the file for reading binary data
    if(load == NULL)//checks if the file was opened successfully
    {
        printf("ERROR: failed to open file");
        return;
    }
    fread(board,64,1,load);//reads the board
    fread(&graveyard1Size,1,1,load);//reads the size of graveyard 1
    fread(player1Graveyard,graveyard1Size,1,load);//reads graveyard 1
    fread(&graveyard2Size,1,1,load);//reads the size of graveyard 2
    fread(player2Graveyard,graveyard2Size,1,load);//reads graveyard 2
    fread(&currentPlayer,1,1,load);//reads the current player
    fclose(load);//closes the file
    turn = 0;//sets the turn to 0 to reset the undo and redo data
    maxTurn = turn;//sets maxTurn equal to turn
}
bool undo()//the function that does the undo operation
{
    if(turn <= 0)//checks if there is a move to undo
    {
        return false;
    }
    else
    {
        currentPlayer = !currentPlayer ;//changes the current player
        if( gameWin != none)//checks if the game state is checkmate or draw
            gameWin = none;
        loadUndoMove();//loads the move to undo
        movePiece(command,board);//moves the piece
        if(deadPieces[turn] != 0)//checks if a piece was captured this turn
        {
            board[command.currentY][command.currentX] = deadPieces[turn];//restores the captured piece
            if(isupper(deadPieces[turn]))//checks which player owns the piece and reduces the size of his graveyard
            {
                graveyard1Size--;
            }
            else
            {
                graveyard2Size--;
            }
        }
        if(promotion[turn] != 0)//checks if a pawn was promoted at this turn
        {
            if(currentPlayer == firstPlayer)//checks which player did the promotion
            {
                board[command.nextY][command.nextX] = 'P';//restores the piece
            }
            else
            {
                board[command.nextY][command.nextX] = 'p';//restores the piece
            }
        }
        turn--;//reduces the turn by one
        printBoard();//prints the board
    }
    return true;
}
void redo()//the function that does the redo operation
{
    if(turn >= maxTurn || turn < 0)//checks if there is a move to redo
    {
        redoErrorPrint = true;//prints an error if there is no move to redo
    }
    else
    {
        loadRedoMove();//loads the move for redo
        movePiece(command,board);//moves the piece
        if(promotion[turn+1] != 0 )//checks if a promotion occurred in this turn
        {
            board[command.nextY][command.nextX] = promotion[turn+1];//does the promotion
        }
        if(deadPieces[turn+1] != 0)
        {
            if(isupper(deadPieces[turn+1]))
                graveyard1Size++;//adds the dead pieces back to graveyard
            else
                graveyard2Size++;
        }
        currentPlayer = !currentPlayer;//changes the current player
        turn++;//increases the turn by one
        printBoard();//prints the board
    }
}
