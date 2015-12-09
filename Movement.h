#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED
bool isFirstMove(void);
bool isNotOccupied(void);
void applyMove(void);
bool isValidEat(char piece);
void movePiece(void);
bool obstaclesExist(char piece);
#endif // MOVEMENT_H_INCLUDED
