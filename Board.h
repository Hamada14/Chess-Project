#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdbool.h>

void printBoard(void);
void resetBoard(void);
void addToDeadPieces();
void saveMove();
void savePromotion();
char board[8][8];
char player1Graveyard[16];
char player2Graveyard[16];
char deadPieces[32];
char promotion[32];
int promotionTurn[32];
int deathTurn[32];
int moves[1000];//Assumption made that the maximum number of turns to be undone is 250 turns
int graveyard1Size;
int graveyard2Size;
int numberOfDeadPieces;
int promotionSize;
bool hasBoard;
#endif // BOARD_H_INCLUDED

