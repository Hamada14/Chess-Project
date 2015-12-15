#ifndef MOVEMENT_H_INCLUDED
#define MOVEMENT_H_INCLUDED
bool isFirstMove(void);
bool isNotOccupied(void);
bool applyMove(void);
bool isValidEat(int x1,int y1,int x2,int y2,char piece);
void movePiece(void);
bool obstaclesExist(int x1 ,int y1 , int x2 , int y2,char piece);
bool checkRightPiece(int x1, int y1);
bool checkSoldier(int x1, int y1, int x2, int y2, char type);
bool checkRook(int x1, int y1, int x2, int y2, char type);
bool checkHorse(int x1, int y1, int x2, int y2, char type);
bool checkBishop(int x1, int y1, int x2, int y2, char type);
bool checkQueen(int x1, int y1, int x2, int y2, char type);
void addToGraveyard(void);
bool isChecked(char king);
#endif // MOVEMENT_H_INCLUDED
