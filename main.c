#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Movement.h"
#include "Board.h"
int main()
{
    printInterface();
    getch();
    system("cls");
    currentPlayer = secondPlayer;
    resetBoard();
    loadGame();
    printBoard();
    applyMove();
    system("cls");
    printBoard();

}
