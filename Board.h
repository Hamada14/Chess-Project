#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <stdbool.h>

void printBoard(void);
void resetBoard(void);
void addToDeadPieces();
void saveMove();
void loadUndoMove();
void loadRedoMove();
void savePromotion();
char board[8][8];
char backupBoard[8][8];
char player1Graveyard[16];
char player2Graveyard[16];
char deadPieces[500];
char deadPiecesTemp[500];
char promotion[500];
int moves[500][4];//Assumption made that the maximum number of turns to be undone is 500 turns
int graveyard1Size;
int graveyard2Size;
int maxTurn;
bool hasBoard;
#endif // BOARD_H_INCLUDED

