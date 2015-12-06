#include <stdio.h>
#include "board.h"
void saveGame(void)
{
    FILE* save;
    save = fopen("save.bin","wb");
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
    load = fopen("save.bin","rb");
    if(load == NULL)
    {
        return;
    }
    fread(board,64,1,load);
    fclose(load);
}
