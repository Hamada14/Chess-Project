#include <stdio.h>
#include "Board.h"
#include "Save.h"
void saveGame(void)
{
    FILE* save;
    save = fopen("save.bin","w");
    if(save == NULL)
    {
        printf("ERROR: failed to open file");
        return;
    }
    fwrite(board,64,1,save);
    fclose(save);
}
void loadGame(void)
{
    FILE* load;
    load = fopen("save.bin","r");
    if(load == NULL)
    {
        printf("ERROR: failed to open file");
        return;
    }
    fread(board,64,1,load);
    fclose(load);
}
