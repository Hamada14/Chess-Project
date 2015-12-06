#include <stdio.h>
char board[8][8];
void printBoard(void)
{
    for(int i = 0 ; i < 8 ; i++)
    {
        printf("\t%c",'A' + i);
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        printf("\n\n\n%d",i);
        for(int j = 0 ; j < 8 ; j++)
        {
            printf("\t%c",board[i][j]);
        }
    }
    printf("\n");
}
void resetBoard(void)
{
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            if(i > 1 && i < 6)
            {
                if( (i + j) % 2 == 0 )
                {
                    board[i][j] = '#';
                }
                else
                {
                    board[i][j] = '-';
                }
            }
            else if (i == 1 || i == 6)
            {
                board[i][j] = 'P';
            }
            else
            {
                if(j == 0 || j == 7)
                {
                    board[i][j] = 'R';
                }
                else if(j == 1 || j == 6)
                {
                    board[i][j] = 'N';
                }
                else if(j == 2 || j == 5)
                {
                    board[i][j] = 'B';
                }
                else if(j == 3)
                {
                    board[i][j] = 'K';
                }
                else
                {
                    board[i][j] = 'Q';
                }
            }
        }
    }
}
