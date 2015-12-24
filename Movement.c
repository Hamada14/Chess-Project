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
        getMove();//gets the move from the player
        if( commandStart)//returns false if its a command and not a move
            return false;
        int x1 = command.currentX ;
        int y1 = command.currentY ;
        int x2 = command.nextX;
        int y2 = command.nextY;
        //checks if the command is in the list of commands that remove the check on the king
        bool kingCheck = !checkIfAvailable( command);
        if( kingCheck)//checks if the move does not remove the check on the king
        {
            clearScreen();//clears the screen
            printBoard();//prints the board
            printError("king check");//prints error if the move does not remove the check on the king
            continue;
        }
            switch(board[command.currentY][command.currentX])//checks if the piece was moved successfully
            {
            case 'P':
            case 'p':
                movedSuccessfully = checkSoldier( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                break;
            case 'R':
            case 'r':
                movedSuccessfully = checkRook(  x1, y1, x2, y2, board[command.currentY][command.currentX]);
                break;
            case 'N':
            case 'n':
                movedSuccessfully = checkHorse( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                break;
            case 'B':
            case 'b':
                movedSuccessfully = checkBishop( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                break;
            case 'Q':
            case 'q':
                movedSuccessfully = checkQueen( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                break;
            case 'K':
            case 'k':
                movedSuccessfully = checkKing( x1, y1, x2, y2, board[command.currentY][command.currentX]);
                break;
            }
        if( !(movedSuccessfully)  )
        {
            clearScreen();//clears the screen
            printBoard();//prints the board
            printError("not valid move");//prints an error if the move was not successful
        }
    }
    while( !(movedSuccessfully) );//checks if the move was successful else it gets another one
    turn++ ;//increments the turn by 1
    maxTurn = turn;//saves the maximum turn for redo
    doPromotion();//does the promotion if it exists
    saveMove();//saves the move for undo and redo
    return true;
}

bool isNotOccupied(void)// checks if the target block is empty
{
    int x = command.nextX,y = command.nextY;
    if(board[y][x]=='#' || board[y][x]=='-')//returns true if the target block is empty
    {
        return true;
    }
    return false ;
}
bool isFirstMove(void)//checks if the current move is the first move for a pawn
{
    int x = command.currentX,y = command.currentY;
    if(board[y][x] == 'P')//returns true if the pawn has not moved
    {
        if(y == 6)
            return true;
        else
            return false;
    }
    else if(board[y][x] == 'p')//returns true if the pawn has not moved
    {
        if(y == 1)
            return true;
        else
            return false;
    }
    return false;
}
bool isValidEat(int x1,int y1,int x2,int y2,char piece)//checks if the move is a valid capture
{
    int deltaY = y2 - y1 , deltaX = x2 - x1;
    switch(piece)
    {
    /*for the pawn this function behaved different it does both checking the move and checking if the piece in the
    target block belongs to the other player*/
    case 'P':
        if(!isNotOccupied())//checks if the position is not empty
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
        if(!(isNotOccupied() ) )//checks if the position is not empty
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
    case 'Q'://checks if the target block is occupied by an opponent's piece
    case 'B':
    case 'N':
    case 'K':
        if( islower( board[y2][x2] ) )
            return true;
        else
            return false;
        break;
    case 'r':
    case 'q':
    case 'b':
    case 'n'://checks if the target block is occupied by an opponent's piece
    case 'k':
        if( isupper( board[y2][x2] ) )
            return true;
        else
            return false;
        break;
    }
    return false;
}
void movePiece(void)// the function that moves the piece
{
    board[command.nextY][command.nextX] = board[command.currentY][command.currentX];// moves the piece
    if((command.currentX + command.currentY) % 2 == 0)
        board[command.currentY][command.currentX] = '#';//resets the position that was occupied by the piece it moved
    else
        board[command.currentY][command.currentX] = '-';
}
//checks if there are any obstacles in the path of any given piece
bool obstaclesExist(int x1 ,int y1 , int x2 , int y2,char piece)
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    switch(piece)
    {
    case 'P':
        if(isFirstMove())//checks if it's the pawn first move
        {
            if(board[y1-1][x1] != '#' && board[y1-1][x1] != '-')//checks if there is a piece blocking the way
                return true;//returns true if a piece is blocking the way
        }
        break;
    case 'p':
        if(isFirstMove())//checks if it's the pawn first move
        {
            if(board[y1+1][x1] != '#' && board[y1+1][x1] != '-')//checks if there is a piece blocking the way
                return true;//returns true if a piece is blocking the way
        }
        break;
    case 'R':
    case 'r':
        if(deltaX == 0)//checks if the move is vertical
        {
            if(y2 > y1)
            {
                for(int y = y1+1 ; y < y2 ; y++)//checks if there is a piece blocking the way
                {
                    if(board[y][x1] != '#' && board[y][x1] != '-')//returns true if a piece is blocking the way
                    {
                        return true;
                    }
                }
            }
            else if(y2 < y1)
            {
                for(int y = y1-1 ; y > y2 ; y--)//checks if there is a piece blocking the way
                {
                    if(board[y][x1] != '#' && board[y][x1] != '-')//returns true if a piece is blocking the way
                    {
                        return true;
                    }
                }
            }
        }
        else if(deltaY == 0)//checks if the move is horizontal
        {
            if(x2 > x1)
            {
                for(int x = x1+1 ; x < x2 ; x++)//checks if there is a piece blocking the way
                {
                    if(board[y1][x] != '#' && board[y1][x] != '-')//returns true if a piece is blocking the way
                    {
                        return true;
                    }
                }
            }
            else if(x2 < x1)
            {
                for(int x = x1-1 ; x > x2 ; x--)//checks if there is a piece blocking the way
                {
                    if(board[y1][x] != '#' && board[y1][x] != '-')//returns true if a piece is blocking the way
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
            for(int x = x1+1, y = y1+1 ; x < x2 ; x++)//checks if there is a piece blocking the way
            {
                if(board[y][x] != '#' && board[y][x] != '-')//returns true if a piece is blocking the way
                    return true;
                y++;
            }
        }
        else if(deltaX == deltaY && x2 < x1)
        {
            for(int x = x1-1, y = y1-1 ; x > x2 ; x--)//checks if there is a piece blocking the way
            {
                if(board[y][x] != '#' && board[y][x] != '-')//returns true if a piece is blocking the way
                    return true;
                y--;
            }
        }
        else if(deltaX == -deltaY && x2 > x1)
        {
            for(int x = x1+1, y = y1-1 ; x < x2 ; x++)//checks if there is a piece blocking the way
            {
                if(board[y][x] != '#' && board[y][x] != '-')//returns true if a piece is blocking the way
                    return true;
                y--;
            }
        }
        else if(deltaX == -deltaY && x2 < x1)
        {
            for(int x = x1-1, y = y1+1 ; x > x2 ; x--)//checks if there is a piece blocking the way
            {
                if(board[y][x] != '#' && board[y][x] != '-')//returns true if a piece is blocking the way
                    return true;
                y++;
            }
        }
        break;

    }
    return false;
}

bool checkRightPiece(int x1, int y1)//checks if the current player can move this piece
{

    switch ( board[y1][x1])
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

    if( currentPlayer == firstPlayer && board[y1][x1] == toupper( board[y1][x1] ) )
        return true;//returns true if the piece belongs to the current player
    else if( currentPlayer == secondPlayer && board[y1][x1] ==  tolower(board[y1][x1]) )
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

bool checkSoldier(int x1, int y1, int x2, int y2, char type)//checks if the given move is a valid move for pawn
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    if( type == 'p' )
        deltaY = -(deltaY);
    if(deltaY == -1 && deltaX == 0 && isNotOccupied())
    {
        movePiece();//moves the piece
        if(!simulation)//checks if it's an actual move or checkmate simulation
        {
            deadPieces[turn+1] = 0;//resets the captured piece at this turn to 0
        }
        return true;
    }
    else if(deltaY == -2 && deltaX == 0 && isNotOccupied() && isFirstMove() && !obstaclesExist(x1,y1,x2,y2,type))
    {
        movePiece();//moves the piece
        if(!simulation)//checks if it's an actual move or checkmate simulation
        {
            deadPieces[turn+1] = 0;//resets the captured piece at this turn to 0
        }
        return true;
    }
    else if(isValidEat(x1,y1,x2,y2,type))
    {
        if(!simulation)//checks if it's an actual move or checkmate simulation
        {
            addToGraveyard();//adds the captured piece to the graveyard of its owner
            addToDeadPieces();//adds the captured piece to the list of captured pieces for undo
        }
        movePiece();//moves the piece
        return true;
    }
    else
    {
        return false;
    }
}

bool checkKing(int x1, int y1, int x2, int y2, char type)//checks if the given move is a valid move for king
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    if( ( (abs(deltaX) == 1 && abs( deltaY) == 0) || ( abs(deltaX) == 1 && abs(deltaY) == 1 ) || (abs(deltaX) == 0 && abs(deltaY) == 1) ))
    {
        if(isValidEat(x1,y1,x2,y2,type))
        {
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                addToGraveyard();//adds the captured piece to the graveyard of its owner
                addToDeadPieces();//adds the captured piece to the list of captured pieces for undo
            }
            movePiece();//moves the piece
            return true;
        }
        if( isNotOccupied())
        {
            movePiece();//moves the piece
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                deadPieces[turn+1] = 0;//resets the captured piece at this turn to 0
            }
            return true;
        }
    }
        return false;
}

bool checkRook( int x1, int y1, int x2, int y2, char type)//checks if the given move is a valid move for rook
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    if( ( (deltaX == 0 && deltaY != 0) || ( deltaX != 0 && deltaY == 0) ) && !obstaclesExist(x1,y1,x2,y2,type))
    {
        if( isNotOccupied() )
        {
            movePiece();//moves the piece
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                deadPieces[turn+1] = 0;//resets the captured piece at this turn to 0
            }
            return true;
        }
        else if( isValidEat(x1,y1,x2,y2,type) )
        {
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                addToGraveyard();//adds the captured piece to the graveyard of its owner
                addToDeadPieces();//adds the captured piece to the list of captured pieces for undo
            }
            movePiece();//moves the piece
            return true;
        }
    }
    return false;
}

bool checkHorse(int x1, int y1, int x2, int y2, char type)//checks if the given move is a valid move for horse
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    if( ( abs(deltaX) == 1 && abs(deltaY) == 2) || ( abs(deltaX) == 2 && abs(deltaY) == 1 ) )
    {
        if( isNotOccupied() )
        {
            movePiece();//moves the piece
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                deadPieces[turn+1] = 0;//resets the captured piece at this turn to 0
            }
            return true;
        }
        else if( isValidEat(x1,y1,x2,y2,type) )
        {
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                addToGraveyard();//adds the captured piece to the graveyard of its owner
                addToDeadPieces();//adds the captured piece to the list of captured pieces for undo
            }
            movePiece();//moves the piece
            return true;
        }
    }
    return false;
}
bool checkBishop(int x1, int y1, int x2, int y2, char type)//checks if the given move is a valid move for bishop
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    // checks if the move is valid and if there are any obstacles in the way
    if( abs(deltaX) == abs(deltaY) && !obstaclesExist(x1,y1,x2,y2,type))
    {
        if( isNotOccupied() )//checks if the new position is already occupied by another piece
        {
            movePiece();//moves the piece
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                deadPieces[turn+1] = 0;//resets the captured piece at this turn to 0
            }
            return true;
        }
        else if( isValidEat(x1,y1,x2,y2,type) )
        {
            if(!simulation)//checks if it's an actual move or checkmate simulation
            {
                addToGraveyard();//adds the captured piece to the graveyard of its owner
                addToDeadPieces();//adds the captured piece to the list of captured pieces for undo
            }
            movePiece();//moves the piece
            return true;
        }
    }
    return false;
}
bool checkQueen(int x1, int y1, int x2, int y2, char type)//checks if the given move is a valid move for queen
{
   if(isupper(type))
   {
       return (checkRook(x1,y1,x2,y2,'R') || checkBishop(x1,y1,x2,y2,'B'));
   }
   else
   {
       return (checkRook(x1,y1,x2,y2,'r') || checkBishop(x1,y1,x2,y2,'b'));
   }
}
void addToGraveyard(void)// adds the piece to the players' respective graveyard
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
bool isChecked()//finds the king and checks if the king is in check
{
    char king;
    if( currentPlayer == firstPlayer)
        king = 'K';
    else
        king = 'k';
    bool kingCase = isupper(king);
    char piece = '\0';
    int kingX,kingY;
    for(int y1 = 0; y1 < 8 ; y1++)//finds the King of the current player
    {
        for(int x1 = 0 ; x1 < 8 ; x1++)
        {
            if(board[y1][x1] == king)//gets the coordinated of the king
            {
                kingY = y1;
                kingX = x1;
                break;
            }
        }
    }
    for(int y1 = 0 ; y1 < 8 ; y1++)//finds out whether the King is in check or not
    {
        for(int x1 = 0 ; x1 < 8 ; x1++)
        {
            if(board[y1][x1]!= '#' && board[y1][x1]!= '-')//checks if the location is empty
                {
                    if(isupper(board[y1][x1]) != kingCase)//checks if the piece belongs to the opponent
                    {
                        piece = board[y1][x1];
                        switch(piece)//returns true if the king is a valid capture for the piece
                        {
                        case 'p':
                        case 'P':
                            if(isValidEat(x1,y1,kingX,kingY,piece))
                            {
                                return true;
                            }
                            break;
                        case 'q':
                        case 'Q':
                            if(checkQueen(x1,y1,kingX,kingY,piece))
                            {
                                return true;
                            }
                            break;
                        case 'b':
                        case 'B':
                            if(checkBishop(x1,y1,kingX,kingY,piece))
                            {
                                return true;
                            }
                            break;
                        case 'r':
                        case 'R':
                            if(checkRook(x1,y1,kingX,kingY,piece))
                            {
                                return true;
                            }
                            break;
                        case 'n':
                        case 'N':
                            if(checkHorse(x1,y1,kingX,kingY,piece))
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
