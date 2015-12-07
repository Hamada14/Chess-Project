#include <stdio.h>
#include "Board.h"
#include "Save.h"
void saveGame(void)
{
    FILE* save;
    save = fopen("save.bin","w");
    if(save == NULL)
    {
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
        return;
    }
    fread(board,64,1,load);
    fclose(load);
}
