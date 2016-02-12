#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "Board.h"
#include "Game.h"
#include "Movement.h"
#include <stdio.h>

char pieces[] = { 'p', 'r','n', 'b', 'q', 'k'};
int pieceSize = sizeof(pieces) / sizeof(pieces[0]);

bool applyMove(void)
{
    bool movedSuccessfully = false ;
    do
    {
        getMove();
        if( commandStart)
            return false;
        bool kingCheck = !checkIfAvailable( command);
        if( kingCheck)
        {
            clearScreen();
            printBoard();
            printError("king check");
            continue;
        }
            switch(board[command.currentY][command.currentX])
            {
            case 'P':
            case 'p':
                movedSuccessfully = checkSoldier(command, board, board[command.currentY][command.currentX]);
                break;
            case 'R':
            case 'r':
                movedSuccessfully = checkRook(command, board, board[command.currentY][command.currentX]);
                break;
            case 'N':
            case 'n':
                movedSuccessfully = checkHorse(command, board, board[command.currentY][command.currentX]);
                break;
            case 'B':
            case 'b':
                movedSuccessfully = checkBishop(command, board, board[command.currentY][command.currentX]);
                break;
            case 'Q':
            case 'q':
                movedSuccessfully = checkQueen(command, board, board[command.currentY][command.currentX]);
                break;
            case 'K':
            case 'k':
                movedSuccessfully = checkKing(command, board, board[command.currentY][command.currentX]);
                break;
            }
        if( !(movedSuccessfully)  )
        {
            clearScreen();
            printBoard();
            printError("not valid move");
        }
    }
    while( !(movedSuccessfully) );
    turn++ ;
    maxTurn = turn;
    doPromotion();
    saveMove();
    return true;
}

bool isNotOccupied(struct commands command,char board[8][8])
{
    int x = command.nextX,y = command.nextY;
    if(board[y][x]=='#' || board[y][x]=='-')
    {
        return true;
    }
    return false ;
}

bool isFirstMove(struct commands command, char board[8][8])
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

bool isValidEat(struct commands command, char board[8][8],char piece)
{
    int deltaY = command.nextY - command.currentY , deltaX = command.nextX - command.currentX;
    switch(piece)
    {
    case 'P':
        if(!isNotOccupied(command,board))
        {
            if( ( deltaX == 1 ) && ( deltaY == -1 ) && islower(board[command.nextY][command.nextX] ))
                return true;
            else if( ( deltaX == -1 ) && ( deltaY == -1 ) && islower(board[command.nextY][command.nextX]))
                return true;
            else
                return false;
        }
        break;
    case 'p':
        if(!(isNotOccupied(command,board) ) )
        {
            if( ( deltaX == 1 ) && ( deltaY == 1 ) && isupper(board[command.nextY][command.nextX]))
                return true;
            else if( ( deltaX == -1 ) && ( deltaY == 1 ) && isupper(board[command.nextY][command.nextX]))
                return true;
            else
                return false;
        }
        break;
    case 'R':
    case 'Q':
    case 'B':
    case 'N':
    case 'K':
        if( islower( board[command.nextY][command.nextX] ) )
            return true;
        else
            return false;
        break;
    case 'r':
    case 'q':
    case 'b':
    case 'n':
    case 'k':
        if( isupper( board[command.nextY][command.nextX] ) )
            return true;
        else
            return false;
        break;
    }
    return false;
}
void movePiece(struct commands command, char board[8][8])
{
    board[command.nextY][command.nextX] = board[command.currentY][command.currentX];
    if((command.currentX + command.currentY) % 2 == 0)
        board[command.currentY][command.currentX] = '#';
    else
        board[command.currentY][command.currentX] = '-';
}

bool obstaclesExist(struct commands command, char board[8][8],char piece)
{
    int x1 = command.currentX, x2 = command.nextX, y1 = command.currentY, y2 = command.nextY;
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    switch(piece)
    {
    case 'P':
        if(isFirstMove(command,board))
        {
            if(board[y1-1][x1] != '#' && board[y1-1][x1] != '-')
                return true;
        }
        break;
    case 'p':
        if(isFirstMove(command,board))
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
    }
    return false;
}

bool checkRightPiece(char type)
{

    switch ( type)
    {
    case '#':
    case '-'://if the player is trying to move an empty block
        if(!simulation)//checks if it's an actual move or checkmate simulation
        {
            clearScreen();//clears the screen
            printBoard();//prints the board
            printError("empty block");//prints an error
        }
        return false;
    }

    if( currentPlayer == firstPlayer && type == toupper( type ) )
        return true;//returns true if the piece belongs to the current player
    else if( currentPlayer == secondPlayer && type ==  tolower(type) )
        return true;//returns true if the piece belongs to the current player
    else//if the player is trying to move a piece that is not his
        if(!simulation)//checks if it's an actual move or checkmate simulation
        {
            clearScreen();//clears the screen
            printBoard();//prints the board
            printError("move one piece");//prints an error
        }
    return false;
}

bool checkSoldier(struct commands command, char board[8][8], char type)
{
    int deltaX = command.nextX - command.currentX;
    int deltaY = command.nextY - command.currentY;
    if( type == 'p' )
        deltaY = -(deltaY);
    if(deltaY == -1 && deltaX == 0 && isNotOccupied(command,board))
    {
        movePiece(command,board);
        if(!simulation)
        {
            deadPieces[turn+1] = 0;
        }
        return true;
    }
    else if(deltaY == -2 && deltaX == 0 && isNotOccupied(command,board) && isFirstMove(command, board) && !obstaclesExist(command,board,type))
    {
        movePiece(command,board);
        if(!simulation)
        {
            deadPieces[turn+1] = 0;
        }
        return true;
    }
    else if(isValidEat(command,board,type))
    {
        if(!simulation)
        {
            addToGraveyard();
            addToDeadPieces();
        }
        movePiece(command,board);
        return true;
    }
    else
    {
        return false;
    }
}

bool checkKing(struct commands command, char board[8][8], char type)
{
    int deltaX = command.nextX - command.currentX;
    int deltaY = command.nextY - command.currentY;
    if( ( (abs(deltaX) == 1 && abs( deltaY) == 0) || ( abs(deltaX) == 1 && abs(deltaY) == 1 ) || (abs(deltaX) == 0 && abs(deltaY) == 1) ))
    {
        if(isValidEat(command,board,type))
        {
            if(!simulation)
            {
                addToGraveyard();
                addToDeadPieces();
            }
            movePiece(command,board);
            return true;
        }
        if( isNotOccupied(command,board))
        {
            movePiece(command,board);
            if(!simulation)
            {
                deadPieces[turn+1] = 0;//resets the captured piece at this turn to 0
            }
            return true;
        }
    }
        return false;
}

bool checkRook(struct commands command, char board[8][8], char type)
{
    int deltaX = command.nextX - command.currentX;
    int deltaY = command.nextY - command.currentY;
    if( ( (deltaX == 0 && deltaY != 0) || ( deltaX != 0 && deltaY == 0) ) && !obstaclesExist(command,board,type))
    {
        if( isNotOccupied(command,board) )
        {
            movePiece(command,board);
            if(!simulation)
            {
                deadPieces[turn+1] = 0;
            }
            return true;
        }
        else if( isValidEat(command,board,type) )
        {
            if(!simulation)
            {
                addToGraveyard();
                addToDeadPieces();
            }
            movePiece(command,board);
            return true;
        }
    }
    return false;
}

bool checkHorse(struct commands command, char board[8][8], char type)//checks if the given move is a valid move for horse
{
    int deltaX = command.nextX - command.currentX;
    int deltaY = command.nextY - command.currentY;
    if( ( abs(deltaX) == 1 && abs(deltaY) == 2) || ( abs(deltaX) == 2 && abs(deltaY) == 1 ) )
    {
        if( isNotOccupied(command,board) )
        {
            movePiece(command, board);
            if(!simulation)
            {
                deadPieces[turn+1] = 0;
            }
            return true;
        }
        else if( isValidEat(command,board,type) )
        {
            if(!simulation)
            {
                addToGraveyard();
                addToDeadPieces();
            }
            movePiece(command,board);
            return true;
        }
    }
    return false;
}
bool checkBishop(struct commands command, char board[8][8], char type)
{
    int deltaX = command.nextX - command.currentX;
    int deltaY = command.nextY - command.currentY;
    if( abs(deltaX) == abs(deltaY) && !obstaclesExist(command,board,type))
    {
        if( isNotOccupied(command,board) )
        {
            movePiece(command,board);
            if(!simulation)
            {
                deadPieces[turn+1] = 0;
            }
            return true;
        }
        else if( isValidEat(command,board,type) )
        {
            if(!simulation)
            {
                addToGraveyard();
                addToDeadPieces();
            }
            movePiece(command,board);
            return true;
        }
    }
    return false;
}

bool checkQueen(struct commands command, char board[8][8], char type)
{
   if(isupper(type))
   {
       return (checkRook(command,board,'R') || checkBishop(command,board,'B'));
   }
   else
   {
       return (checkRook(command,board,'r') || checkBishop(command,board,'b'));
   }
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

bool isChecked(char lastBoard[8][8])
{
    char board[8][8];
    copyFromToBoard(lastBoard,board);
    char king;
    if( currentPlayer == firstPlayer)
        king = 'K';
    else
        king = 'k';
    bool kingCase = isupper(king);
    char piece = '\0';
    int kingX = 0,kingY = 0;
    for(int y1 = 0; y1 < 8 ; y1++)
    {
        for(int x1 = 0 ; x1 < 8 ; x1++)
        {
            if(board[y1][x1] == king)
            {
                kingY = y1;
                kingX = x1;
                break;
            }
        }
    }
    command.nextX = kingX, command.nextY = kingY;
    for(int y1 = 0 ; y1 < 8 ; y1++)
    {
        for(int x1 = 0 ; x1 < 8 ; x1++)
        {
            command.currentX = x1, command.currentY = y1;
            if(board[y1][x1]!= '#' && board[y1][x1]!= '-')
                {
                    if(isupper(board[y1][x1]) != kingCase)
                    {
                        piece = board[y1][x1];
                        switch(piece)
                        {
                        case 'p':
                        case 'P':
                            if(isValidEat(command,board,piece))
                            {
                                return true;
                            }
                            break;
                        case 'q':
                        case 'Q':
                            if(checkQueen(command,board,piece))
                            {
                                return true;
                            }
                            break;
                        case 'b':
                        case 'B':
                            if(checkBishop(command,board,piece))
                            {
                                return true;
                            }
                            break;
                        case 'r':
                        case 'R':
                            if(checkRook(command,board,piece))
                            {
                                return true;
                            }
                            break;
                        case 'n':
                        case 'N':
                            if(checkHorse(command,board,piece))
                            {
                                return true;
                            }
                            break;

                        }
                    }
                }
        }
    }
    return false;
}
