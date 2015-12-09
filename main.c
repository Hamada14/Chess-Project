#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Movement.h"
#include "Board.h"
int main()
{
    currentPlayer = firstPlayer;
    resetBoard();
    printBoard();
    getMove();
    applyMove();
    system("cls");
    printBoard();

}
