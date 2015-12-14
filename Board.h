#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdbool.h>

void printBoard(void);
int compare (const void * a, const void * b);
void resetBoard(void);
char board[8][8];
char player1Graveyard[16];
char player2Graveyard[16];
int graveyard1Size;
int graveyard2Size;
bool hasBoard;
#endif // BOARD_H_INCLUDED

