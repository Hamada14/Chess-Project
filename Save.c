#include <stdio.h>
#include <stdbool.h>
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
    fclose(load);
}
void undo()
{
    if(turn == 0)
    {
        printf("error! nothing to undo");
    }
    else
    {
        currentPlayer = !currentPlayer ;
        bool isDeathTurn = true;
        loadMove();
        movePiece();
        int turnPosition = binarySearch(deathTurn,turn,0,numberOfDeadPieces,&isDeathTurn);
        if(isDeathTurn)
        {
            board[command.currentY][command.currentX] = deadPieces[turnPosition];
        }
        bool isPromotionTurn = true;
        turnPosition = binarySearch(promotionTurn,turn,0,promotionSize,&isPromotionTurn);
        if(isPromotionTurn)
        {
            if(currentPlayer == firstPlayer)
            {
                board[command.currentY][command.currentX] = 'P';
            }
            else
            {
                board[command.currentY][command.currentX] = 'p';
            }
        }
        turn--;
    }
}
int binarySearch (int A[],int key, int minA, int maxA,bool *isFound)
{
    *isFound = true;
    int midA =(minA+maxA)/2;
    if (minA>maxA)
    {
        *isFound = false;
        return -1;
    }
    if(key < A[midA])
    {
        return binarySearch(A,key,minA,midA-1);
    }
    else if (key > A[midA])
    {
        return binarySearch(A,key,midA+1,maxA);
    }
    else
        return midA;
}
