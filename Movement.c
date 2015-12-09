#ifndef MOVEMENT_C_INCLUDED
#define MOVEMENT_C_INCLUDED
#include <stdbool.h>
#include <ctype.h>
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
                else if(isValidEat('P'))
                {
                    //add eaten piece to graveyard
                    movePiece();
                    movedSuccessfully = true;
                }
                else
                {
                    getMove();
                }
                break;
        case 'R':
                if(deltaX == 0 && deltaY != 0  && !obstaclesExist('R'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('R') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if(deltaX != 0 && deltaY == 0  && ! obstaclesExist('R'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('R') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }

                else
                {
                    getMove();
                }
                break;
        case 'N':
                if( deltaX == 1 && deltaY == 2 )
                {
                   if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -1 && deltaY == 2 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == 1 && deltaY == -2 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -1 && deltaY == -2 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == 2 && deltaY == 1 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -2 && deltaY == 1 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == 2 && deltaY == -1 )
                {
                   if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -2 && deltaY == -1 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('N') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else
                {
                    getMove();
                }
                break;
        case 'B':
                if(deltaX == deltaY && !obstaclesExist('B'))
                {
                   if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('B') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if (deltaX == -deltaY && !obstaclesExist('B'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('B') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else
                {
                    getMove();
                }
                break;
        case 'Q':
                if(deltaX == 0 && deltaY != 0 && !obstaclesExist('Q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('Q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if(deltaX != 0 && deltaY == 0 && !obstaclesExist('Q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('Q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if(deltaX == deltaY && !obstaclesExist('Q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('Q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if (deltaX == -deltaY && !obstaclesExist('Q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('Q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else
                {
                    getMove();
                }
                break;
        }
    }
    else if(currentPlayer == secondPlayer)
    {
        switch(board[command.currentY][command.currentX])
        {
        case 'p':
                if(deltaY == 1 && deltaX == 0 && isNotOccupied())
                {
                        movePiece();
                        movedSuccessfully = true;
                }
                else if(deltaY == 2 && deltaX == 0 && isNotOccupied() && isFirstMove() && !obstaclesExist('p'))
                {
                        movePiece();
                        movedSuccessfully = true;
                }
                else if(isValidEat('p'))
                {
                    //add eaten piece to graveyard
                    movePiece();
                    movedSuccessfully = true;
                }
                else
                {
                    getMove();
                }
                break;
        case 'r':
                if(deltaX == 0 && deltaY != 0 && !obstaclesExist('r'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('r') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if(deltaX != 0 && deltaY == 0 && ! obstaclesExist('r'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('r') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else
                {
                    getMove();
                }
                break;
        case 'n':
                if( deltaX == 1 && deltaY == 2 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -1 && deltaY == 2 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == 1 && deltaY == -2 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -1 && deltaY == -2 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == 2 && deltaY == 1 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -2 && deltaY == 1 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == 2 && deltaY == -1 )
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if( deltaX == -2 && deltaY == -1 )
                {
                   if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('n') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else
                {
                    getMove();
                }
                break;
        case 'b':
                if(deltaX == deltaY && !obstaclesExist('b'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('b') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if (deltaX == -deltaY && !obstaclesExist('b'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('b') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else
                {
                    getMove();
                }
                break;
        case 'q':
                if(deltaX == 0 && deltaY != 0 && !obstaclesExist('q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if(deltaX != 0 && deltaY == 0 && !obstaclesExist('q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if(deltaX == deltaY && !obstaclesExist('q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
                else if (deltaX == -deltaY && !obstaclesExist('q'))
                {
                    if( isNotOccupied() )
                    {
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else if( isValidEat('q') )
                    {
                        //add eaten piece to graveyard
                        movePiece();
                        movedSuccessfully = true;
                    }
                    else
                    {
                        getMove();
                    }
                }
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
    int x2 = command.nextX , y2 = command.nextY;
    int x1 = command.currentX , y1 = command.currentY;
    int deltaY = y2 - y1 , deltaX = x2 - x1;
    switch(piece)
    {
    case 'P':
        if(!isNotOccupied())
        {
            if( ( deltaX == 1 ) && ( deltaY == -1 ) && islower(board[y2][x2] ))
                    return true;
            else if( ( deltaX == -1 ) && ( deltaY == -1 ) && islower(board[y2][x2]))
                    return true;
            else
                    return false;
        }
        break;
    case 'p':
        if(!isNotOccupied())
        {
            if( ( deltaX == 1 ) && ( deltaY == 1 ) && isupper(board[y2][x2]))
                    return true;
            else if( ( deltaX == -1 ) && ( deltaY == 1 ) && isupper(board[y2][x2]))
                    return true;
            else
                    return false;
        }
        break;
    case 'R':
    case 'Q':
    case 'B':
    case 'N':
        if( islower( board[y2][x2] ) )
                return true;
        else
                return false;
        break;
    case 'r':
    case 'q':
    case 'b':
    case 'n':
        if( isupper( board[y2][x2] ) )
                return true;
        else
                return false;
        break;
    }
    return false;
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
