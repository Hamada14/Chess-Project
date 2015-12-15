#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdbool.h>

void printBoard(void);
void resetBoard(void);
void addToDeadPieces();
char board[8][8];
char player1Graveyard[16];
char player2Graveyard[16];
char deadPieces[32];
int deathTurn[32];
int moves[1000];
int graveyard1Size;
int graveyard2Size;
int numberOfDeadPieces;
bool hasBoard;
#endif // BOARD_H_INCLUDED

