<<<<<<< HEAD
#ifndef MOVEMENT_C_INCLUDED
#define MOVEMENT_C_INCLUDED
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "Board.h"
#include "Game.h"
#include "Movement.h"

char pieces[] = { 'p', 'r','n', 'b', 'q', 'k'};
int pieceSize = sizeof(pieces) / sizeof(pieces[0]);

bool applyMove(void)
{
    bool movedSuccessfully = false ;
    do{
        getMove();
        if( commandStart)
        return false;
        int deltaX = command.nextX - command.currentX ;
        int deltaY = command.nextY - command.currentY ;
        if( checkRightPiece() )
            switch(board[command.currentY][command.currentX])
            {
            case 'P':
            case 'p':
                movedSuccessfully = checkSoldier( deltaX, deltaY, board[command.currentY][command.currentX]);
                break;
            case 'R':
            case 'r':
                movedSuccessfully = checkRook( deltaX, deltaY, board[command.currentY][command.currentX]);
                break;
            case 'N':
            case 'n':
                movedSuccessfully = checkHorse(deltaX, deltaY, board[command.currentY][command.currentX]);
                break;
            case 'B':
            case 'b':
                movedSuccessfully = checkBishop(deltaX, deltaY, board[command.currentY][command.currentX]);
            break;
            case 'Q':
            case 'q':
                movedSuccessfully = checkQueen(deltaX, deltaY, board[command.currentY][command.currentX]);
                break;
            }
        else
        {
            printError("not valid move");
            continue;
        }
        if( !(movedSuccessfully) )
        {
            printError("not valid move");
        }
    }while( !(movedSuccessfully) );
    doPromotion();
    turn++;
    return true;
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

bool checkRightPiece()
{

    switch ( board[command.currentY][command.currentX])
    {
    case '#':
    case '-':
        printError("empty block");
        return false;
    }

    if( currentPlayer == firstPlayer && board[command.currentY][command.currentX] == toupper( board[command.currentY][command.currentX] ) )
            return true;
    if( currentPlayer == secondPlayer && board[command.currentY][command.currentX] ==  tolower(board[command.currentY][command.currentX]) )
            return true;

    return false;
}

bool checkSoldier( int deltaX, int deltaY, char type)
{
    if( type == 'p' )
        deltaY = -(deltaY);
    if(deltaY == -1 && deltaX == 0 && isNotOccupied())
    {
        movePiece();
        return true;
    }
    else if(deltaY == -2 && deltaX == 0 && isNotOccupied() && isFirstMove() && !obstaclesExist(type))
    {
        movePiece();
        return true;
    }
    else if(isValidEat(type))
    {
        addToGraveyard();
        movePiece();
        return true;
    }
    else
    {
        return false;
    }
}

bool checkRook( int deltaX, int deltaY, char type)
{
    if( ( (deltaX == 0 && deltaY != 0) || ( deltaX != 0 && deltaY == 0) ) && !obstaclesExist(type))
    {
        if( isNotOccupied() )
        {
            movePiece();
            return true;
        }
        else if( isValidEat(type) )
        {
            addToGraveyard();
            movePiece();
            return true;
        }
    }
    return false;
}

bool checkHorse(int deltaX, int deltaY, char type)
{
    if( ( abs(deltaX) == 1 && abs(deltaY) == 2) || ( abs(deltaX) == 2 && abs(deltaY) == 1 ) )
    {
        if( isNotOccupied() )
        {
            movePiece();
            return true;
        }
        else if( isValidEat(type) )
        {
            addToGraveyard();
            movePiece();
            return true;
        }
    }
    return false;
}
bool checkBishop(int deltaX, int deltaY, char type)
{
    if( abs(deltaX) == abs(deltaY) && !obstaclesExist(type))
    {
        if( isNotOccupied() )
        {
            movePiece();
            return true;
        }
        else if( isValidEat(type) )
        {
            addToGraveyard();
            movePiece();
            return true;
        }
    }
    return false;
}
bool checkQueen( int deltaX, int deltaY, char type)
{
    if( ( (deltaX == 0 && deltaY != 0) || ( deltaX != 0 && deltaY == 0) ) && !obstaclesExist(type))
    {
        if( isNotOccupied() )
        {
            movePiece();
            return true;
        }
        else if( isValidEat(type) )
        {
            addToGraveyard();
            movePiece();
            return true;
        }
    }
    else if( abs(deltaX) == abs(deltaY) && !obstaclesExist(type))
    {
        if( isNotOccupied() )
        {
            movePiece();
            return true;
        }
        else if( isValidEat(type) )
        {
            addToGraveyard();
            movePiece();
            return true;
        }
    }
    return false;
}
void addToGraveyard(void)
{
    if(currentPlayer == firstPlayer)
    {
        player2Graveyard[graveyard2Size++] = board[command.nextY][command.nextX];
    }
    else
    {
        player1Graveyard[graveyard1Size++] = board[command.nextY][command.nextX];
    }
}
#endif // MOVEMENT_C_INCLUDED
=======
#ifndef MOVEMENT_C_INCLUDED
#define MOVEMENT_C_INCLUDED
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "Board.h"
#include "Game.h"
#include "Movement.h"

char pieces[] = { 'p', 'r','n', 'b', 'q', 'k'};
int pieceSize = sizeof(pieces) / sizeof(pieces[0]);

bool applyMove(void)
{
        bool movedSuccessfully = false ;
        do {
                        getMove();
                        if( commandStart)
                                return false;
                        int deltaX = command.nextX - command.currentX ;
                        int deltaY = command.nextY - command.currentY ;
                        if( checkRightPiece() )
                                switch(board[command.currentY][command.currentX]) {
                                                case 'P':
                                                case 'p':
                                                        acceptedMove = checkSoldier( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                                                        break;
                                                case 'R':
                                                case 'r':
                                                        acceptedMove = checkRook(  x1, y1, x2, y2, board[command.currentY][command.currentX]);
                                                        break;
                                                case 'N':
                                                case 'n':
                                                        acceptedMove = checkHorse( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                                                        break;
                                                case 'B':
                                                case 'b':
                                                        acceptedMove = checkBishop( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                                                        break;
                                                case 'Q':
                                                case 'q':
                                                        acceptedMove = checkQueen( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                                                        break;
                                        }
                        else {
                                        printError("not valid move");
                                        continue;
                                }
                        if( !(movedSuccessfully) ) {
                                        printError("not valid move");
                                }
                }
        while( !(movedSuccessfully) );
        doPromotion();
        return true;
}

bool isNotOccupied(void)
{
        int x = command.nextX,y = command.nextY;
        if(board[y][x]=='#' || board[y][x]=='-') {
                        return true;
                }
        return false ;
}
bool isFirstMove(void)
{
        int x = command.currentX,y = command.currentY;
        if(board[y][x] == 'P') {
                        if(y == 6)
                                return true;
                        else
                                return false;
                }
        else if(board[y][x] == 'p') {
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
        switch(piece) {
                        case 'P':
                                if(!isNotOccupied()) {
                                                if( ( deltaX == 1 ) && ( deltaY == -1 ) && islower(board[y2][x2] ))
                                                        return true;
                                                else if( ( deltaX == -1 ) && ( deltaY == -1 ) && islower(board[y2][x2]))
                                                        return true;
                                                else
                                                        return false;
                                        }
                                break;
                        case 'p':
                                if(!isNotOccupied()) {
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
        switch(piece) {
                        case 'P':
                                if(isFirstMove()) {
                                                if(board[y1-1][x1] != '#' && board[y1-1][x1] != '-')
                                                        return true;
                                        }
                                break;
                        case 'p':
                                if(isFirstMove()) {
                                                if(board[y1+1][x1] != '#' && board[y1+1][x1] != '-')
                                                        return true;
                                        }
                                break;
                        case 'R':
                        case 'r':
                                if(deltaX == 0) {
                                                if(y2 > y1) {
                                                                for(int y = y1+1 ; y < y2 ; y++) {
                                                                                if(board[y][x1] != '#' && board[y][x1] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                                else if(y2 < y1) {
                                                                for(int y = y1-1 ; y > y2 ; y--) {
                                                                                if(board[y][x1] != '#' && board[y][x1] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                        }
                                else if(deltaY == 0) {
                                                if(x2 > x1) {
                                                                for(int x = x1+1 ; x < x2 ; x++) {
                                                                                if(board[y1][x] != '#' && board[y1][x] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                                else if(x2 < x1) {
                                                                for(int x = x1-1 ; x > x2 ; x--) {
                                                                                if(board[y1][x] != '#' && board[y1][x] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                        }
                                break;
                        case 'B':
                        case 'b':
                                if(deltaX == deltaY && x2 > x1) {
                                                for(int x = x1+1, y = y1+1 ; x < x2 ; x++) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y++;
                                                        }
                                        }
                                else if(deltaX == deltaY && x2 < x1) {
                                                for(int x = x1-1, y = y1-1 ; x > x2 ; x--) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y--;
                                                        }
                                        }
                                else if(deltaX == -deltaY && x2 > x1) {
                                                for(int x = x1+1, y = y1-1 ; x < x2 ; x++) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y--;
                                                        }
                                        }
                                else if(deltaX == -deltaY && x2 < x1) {
                                                for(int x = x1-1, y = y1+1 ; x > x2 ; x--) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y++;
                                                        }
                                        }
                                break;
                        case 'Q':
                        case 'q':
                                if(deltaX == 0) {
                                                if(y2 > y1) {
                                                                for(int y = y1+1 ; y < y2 ; y++) {
                                                                                if(board[y][x1] != '#' && board[y][x1] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                                else if(y2 < y1) {
                                                                for(int y = y1-1 ; y > y2 ; y--) {
                                                                                if(board[y][x1] != '#' && board[y][x1] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                        }
                                else if(deltaY == 0) {
                                                if(x2 > x1) {
                                                                for(int x = x1+1 ; x < x2 ; x++) {
                                                                                if(board[y1][x] != '#' && board[y1][x] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                                else if(x2 < x1) {
                                                                for(int x = x1-1 ; x > x2 ; x--) {
                                                                                if(board[y1][x] != '#' && board[y1][x] != '-') {
                                                                                                return true;
                                                                                        }
                                                                        }
                                                        }
                                        }
                                else if(deltaX == deltaY && x2 > x1) {
                                                for(int x = x1+1, y = y1+1 ; x < x2 ; x++) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y++;
                                                        }
                                        }
                                else if(deltaX == deltaY && x2 < x1) {
                                                for(int x = x1-1, y = y1-1 ; x > x2 ; x--) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y--;
                                                        }
                                        }
                                else if(deltaX == -deltaY && x2 > x1) {
                                                for(int x = x1+1, y = y1-1 ; x < x2 ; x++) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y--;
                                                        }
                                        }
                                else if(deltaX == -deltaY && x2 < x1) {
                                                for(int x = x1-1, y = y1+1 ; x > x2 ; x--) {
                                                                if(board[y][x] != '#' && board[y][x] != '-')
                                                                        return true;
                                                                y++;
                                                        }
                                        }
                                break;
                }
        return false;
}

bool checkRightPiece()
{

        switch ( board[command.currentY][command.currentX]) {
                        case '#':
                        case '-':
                                printError("empty block");
                                return false;
                }

        if( currentPlayer == firstPlayer && board[command.currentY][command.currentX] == toupper( board[command.currentY][command.currentX] ) )
                return true;
        if( currentPlayer == secondPlayer && board[command.currentY][command.currentX] ==  tolower(board[command.currentY][command.currentX]) )
                return true;

        return false;
}

bool checkSoldier(int x1, int y1, int x2, int y2, char type)
{
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;
        if( type == 'p' )
                deltaY = -(deltaY);
        if(deltaY == -1 && deltaX == 0 && isNotOccupied()) {
                        movePiece();
                        return true;
                }
        else if(deltaY == -2 && deltaX == 0 && isNotOccupied() && isFirstMove() && !obstaclesExist(type)) {
                        movePiece();
                        return true;
                }
        else if(isValidEat(type)) {
                        addToGraveyard();
                        movePiece();
                        return true;
                }
        else {
                        return false;
                }
}

bool checkRook( int x1, int y1, int x2, int y2, char type)
{
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;
        if( ( (deltaX == 0 && deltaY != 0) || ( deltaX != 0 && deltaY == 0) ) && !obstaclesExist(type)) {
                        if( isNotOccupied() ) {
                                        movePiece();
                                        return true;
                                }
                        else if( isValidEat(type) ) {
                                        addToGraveyard();
                                        movePiece();
                                        return true;
                                }
                }
        return false;
}

bool checkHorse(int x1, int y1, int x2, int y2, char type)
{
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;
        if( ( abs(deltaX) == 1 && abs(deltaY) == 2) || ( abs(deltaX) == 2 && abs(deltaY) == 1 ) ) {
                        if( isNotOccupied() ) {
                                        movePiece();
                                        return true;
                                }
                        else if( isValidEat(type) ) {
                                        addToGraveyard();
                                        movePiece();
                                        return true;
                                }
                }
        return false;
}
bool checkBishop(int x1, int y1, int x2, int y2, char type)
{
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;
        if( abs(deltaX) == abs(deltaY) && !obstaclesExist(type)) {
                        if( isNotOccupied() ) {
                                        movePiece();
                                        return true;
                                }
                        else if( isValidEat(type) ) {
                                        addToGraveyard();
                                        movePiece();
                                        return true;
                                }
                }
        return false;
}
bool checkQueen(int x1, int y1, int x2, int y2, char type)
{
        int deltaX = x2 - x1;
        int deltaY = y2 - y1;
        if( ( (deltaX == 0 && deltaY != 0) || ( deltaX != 0 && deltaY == 0) ) && !obstaclesExist(type)) {
                        if( isNotOccupied() ) {
                                        movePiece();
                                        return true;
                                }
                        else if( isValidEat(type) ) {
                                        addToGraveyard();
                                        movePiece();
                                        return true;
                                }
                }
        else if( abs(deltaX) == abs(deltaY) && !obstaclesExist(type)) {
                        if( isNotOccupied() ) {
                                        movePiece();
                                        return true;
                                }
                        else if( isValidEat(type) ) {
                                        addToGraveyard();
                                        movePiece();
                                        return true;
                                }
                }
        return false;
}
void addToGraveyard(void)
{
        if(currentPlayer == firstPlayer) {
                        player2Graveyard[graveyard2Size++] = board[command.nextY][command.nextX];
                }
        else {
                        player1Graveyard[graveyard1Size++] = board[command.nextY][command.nextX];
                }
}
#endif // MOVEMENT_C_INCLUDED
>>>>>>> d4828c466271c63f1b8d4ca3ff0f5164384a1874
