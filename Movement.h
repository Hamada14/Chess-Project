#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED
bool isFirstMove(void);
bool isNotOccupied(void);
bool applyMove(void);
bool isValidEat(char piece);
void movePiece(void);
bool obstaclesExist(char piece);
bool checkRightPiece();
bool checkSoldier( int deltaX, int deltaY, char type);
bool checkRook( int deltaX, int deltaY, char type);
bool checkHorse(int deltaX, int deltaY, char type);
bool checkBishop(int deltaX, int deltaY, char type);
bool checkQueen( int deltaX, int deltaY, char type);

#endif // MOVEMENT_H_INCLUDED
