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
char player1Graveyard[16];
char player2Graveyard[16];
char deadPieces[250];
char deadPiecesTemp[250];
char promotion[250];
char promotionTemp[250];
int moves[250][4];//Assumption made that the maximum number of turns to be undone is 250 turns
int graveyard1Size;
int graveyard2Size;
int maxTurn,minTurn;
bool hasBoard;
bool isUndone;
void resetDeadPieces();
#endif // BOARD_H_INCLUDED

