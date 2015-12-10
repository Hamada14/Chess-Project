#include <stdio.h>
#include "Board.h"
#include "Save.h"
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
