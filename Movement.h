#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED
bool isFirstMove(struct commands command, char board[8][8]);
bool isNotOccupied(struct commands command, char board[8][8]);
bool applyMove(void);
bool isValidEat(struct commands command, char board[8][8],char piece);
void movePiece(struct commands command, char board[8][8]);
bool obstaclesExist(struct commands command, char board[8][8],char piece);
bool checkRightPiece(char type);
bool checkSoldier(struct commands command, char board[8][8], char type);
bool checkKing(struct commands command, char board[8][8], char type);
bool checkRook(struct commands command, char board[8][8], char type);
bool checkHorse(struct commands command, char board[8][8], char type);
bool checkBishop(struct commands command, char board[8][8], char type);
bool checkQueen(struct commands command, char board[8][8], char type);
void addToGraveyard(void);
bool isChecked(char lastBoard[8][8]);
#endif // MOVEMENT_H_INCLUDED
