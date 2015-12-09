#ifndef MOVEMENT_C_INCLUDED
#define MOVEMENT_C_INCLUDED
#include <stdbool.h>
#include "Board.h"
#include "Game.h"
#include "Movement.h"
void applyMove(void)
{
    int deltaX = command.nextX - command.currentX ;
    int deltaY = command.nextY - command.currentY ;
    bool movedSuccessfully = false ;
    if(currentPlayer == firstPlayer)
    {
        switch(board[command.currentY][command.currentX])
        {
        case 'P':
                if(deltaY == -1 && deltaX == 0 && isNotOccupied())
                {
                        movePiece();
                        movedSuccessfully = true;
                }
                else if(deltaY == -2 && deltaX == 0 && isNotOccupied() && isFirstMove() && !obstaclesExist('P'))
                {
                        movePiece();
                        movedSuccessfully = true;
                }
                /*else if(isValidEat('P'))
                {
                    //add eaten piece to graveyard
                    movePiece();
                    movedSuccessfully = true;
                }*/
                else
                {
                    getMove();
                }
                break;
        case 'R':
                if(deltaX == 0 && deltaY != 0 && isNotOccupied() && !obstaclesExist('R'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX != 0 && deltaY == 0 && isNotOccupied() && ! obstaclesExist('R'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                /*else if(isValidEat('R'))
                {
                    //add eaten piece to graveyard
                    movePiece();
                    movedSuccessfully = true;
                }*/
                else
                {
                    getMove();
                }
                break;
        case 'N':
                if(deltaX == 1 && deltaY == 2 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == -1 && deltaY == 2 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == 1 && deltaY == -2 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == -1 && deltaY == -2 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == 2 && deltaY == 1 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == -2 && deltaY == 1 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == 2 && deltaY == -1 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == -2 && deltaY == -1 && isNotOccupied())
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                /*else if(isValidEat('N'))
                {
                    //add eaten piece to graveyard
                    movePiece();
                    movedSuccessfully = true;
                }*/
                else
                {
                    getMove();
                }
                break;
        case 'B':
                if(deltaX == deltaY && isNotOccupied() && !obstaclesExist('B'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if (deltaX == -deltaY && isNotOccupied() && !obstaclesExist('B'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
               /* else if(isValidEat('B'))
                {
                    //add eaten piece to graveyard
                    movePiece();
                    movedSuccessfully = true;
                }*/
                else
                {
                    getMove();
                }
                break;
        case 'Q':
                if(deltaX == 0 && deltaY != 0 && isNotOccupied() && !obstaclesExist('Q'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX != 0 && deltaY == 0 && isNotOccupied() && !obstaclesExist('Q'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if(deltaX == deltaY && isNotOccupied() && !obstaclesExist('Q'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
                else if (deltaX == -deltaY && isNotOccupied() && !obstaclesExist('Q'))
                {
                    movePiece();
                    movedSuccessfully = true;
                }
               /* else if(isValidEat('Q'))
                {
                    //add eaten piece to graveyard
                    movePiece();
                    movedSuccessfully = true;
                }*/
                else
                {
                    getMove();
                }
                break;
        }
    }
}
bool isNotOccupied(void)
{
    int x = command.nextX,y = command.nextY;
    if(board[y][x]=='#' || board[y][x]=='-')
    {
        return true;
    }
    return false ;
}
bool isFirstMove(void)
{
    int x = command.currentX,y = command.currentY;
    if(board[y][x] == 'P')
    {
        if(y == 6)
            return true;
        else
            return false;
    }
    else if(board[y][x] == 'p')
    {
        if(y == 1)
            return true;
        else
            return false;
    }
    return false;
}
bool isValidEat(char piece)
{
    //TODO
}
void movePiece(void)
{
    board[command.nextY][command.nextX] = board[command.currentY][command.currentX];
    if((command.currentX + command.currentY) % 2 == 0)
            board[command.currentY][command.currentX] = '#';
    else
            board[command.currentY][command.currentX] = '-';
}
bool obstaclesExist(char piece)
{
    int x1 = command.currentX,x2 = command.nextX;
    int y1 = command.currentY,y2 = command.nextY;
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    switch(piece)
    {
    case 'P':
            if(isFirstMove())
            {
                if(board[y1-1][x1] != '#' && board[y1-1][x1] != '-')
                        return true;
            }
            break;
    case 'p':
            if(isFirstMove())
            {
                if(board[y1+1][x1] != '#' && board[y1+1][x1] != '-')
                        return true;
            }
            break;
    case 'R':
    case 'r':
            if(deltaX == 0)
            {
                if(y2 > y1)
                {
                    for(int y = y1+1 ; y < y2 ; y++)
                    {
                        if(board[y][x1] != '#' && board[y][x1] != '-')
                        {
                            return true;
                        }
                    }
                }
                else if(y2 < y1)
                {
                    for(int y = y1-1 ; y > y2 ; y--)
                    {
                        if(board[y][x1] != '#' && board[y][x1] != '-')
                        {
                            return true;
                        }
                    }
                }
            }
            else if(deltaY == 0)
            {
                if(x2 > x1)
                {
                    for(int x = x1+1 ; x < x2 ; x++)
                    {
                        if(board[y1][x] != '#' && board[y1][x] != '-')
                        {
                            return true;
                        }
                    }
                }
                else if(x2 < x1)
                {
                    for(int x = x1-1 ; x > x2 ; x--)
                    {
                        if(board[y1][x] != '#' && board[y1][x] != '-')
                        {
                            return true;
                        }
                    }
                }
            }
            break;
    case 'B':
    case 'b':
            if(deltaX == deltaY && x2 > x1)
            {
                for(int x = x1+1, y = y1+1 ; x < x2 ; x++)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y++;
                }
            }
            else if(deltaX == deltaY && x2 < x1)
            {
                for(int x = x1-1, y = y1-1 ; x > x2 ; x--)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y--;
                }
            }
            else if(deltaX == -deltaY && x2 > x1)
            {
                for(int x = x1+1, y = y1-1 ; x < x2 ; x++)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y--;
                }
            }
            else if(deltaX == -deltaY && x2 < x1)
            {
                for(int x = x1-1, y = y1+1 ; x > x2 ; x--)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y++;
                }
            }
            break;
    case 'Q':
    case 'q':
            if(deltaX == 0)
            {
                if(y2 > y1)
                {
                    for(int y = y1+1 ; y < y2 ; y++)
                    {
                        if(board[y][x1] != '#' && board[y][x1] != '-')
                        {
                            return true;
                        }
                    }
                }
                else if(y2 < y1)
                {
                    for(int y = y1-1 ; y > y2 ; y--)
                    {
                        if(board[y][x1] != '#' && board[y][x1] != '-')
                        {
                            return true;
                        }
                    }
                }
            }
            else if(deltaY == 0)
            {
                if(x2 > x1)
                {
                    for(int x = x1+1 ; x < x2 ; x++)
                    {
                        if(board[y1][x] != '#' && board[y1][x] != '-')
                        {
                            return true;
                        }
                    }
                }
                else if(x2 < x1)
                {
                    for(int x = x1-1 ; x > x2 ; x--)
                    {
                        if(board[y1][x] != '#' && board[y1][x] != '-')
                        {
                            return true;
                        }
                    }
                }
            }
            else if(deltaX == deltaY && x2 > x1)
            {
                for(int x = x1+1, y = y1+1 ; x < x2 ; x++)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y++;
                }
            }
            else if(deltaX == deltaY && x2 < x1)
            {
                for(int x = x1-1, y = y1-1 ; x > x2 ; x--)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y--;
                }
            }
            else if(deltaX == -deltaY && x2 > x1)
            {
                for(int x = x1+1, y = y1-1 ; x < x2 ; x++)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y--;
                }
            }
            else if(deltaX == -deltaY && x2 < x1)
            {
                for(int x = x1-1, y = y1+1 ; x > x2 ; x--)
                {
                    if(board[y][x] != '#' && board[y][x] != '-')
                        return true;
                    y++;
                }
            }
            break;
    }
    return false;
}
#endif // MOVEMENT_C_INCLUDED
