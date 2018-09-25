
/* 
 * File:   Board.h
 * Author: Michael Wooll
 * Board class
 * Created on May 8, 2018, 3:23 PM
 */

#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "CPU.h"


class Board {
public:
    Board(int rowIn = 6, int colIn = 7); // Default to 6 rows and 7 cols (standard game)
    ~Board();
    
    //Copy constructor
    Board(Board&);
    
    void print();
    int placePiece(); // Places the game piece for the player at specified column
    int placeTestPiece(int); // Function used by AI to simulate
    int placeAIPiece(int); // Places AI piece at specified column
    int checkWin(); // Checks if there are 4 in a row. (Returns 1 if player won, 2 if CPU won, and 0 if no win)
    int AI(); //AI turn
    void play(); // Game loop
    bool isColFull(int); // Returns true of a column is full, false if not
    bool isConnect(int);
    void setDiff();
    void start(); // Starts game by creating users and keeps playing until player decides to quit
    void reset();
    void setPlayer(Player p){p1 = p;}
    void multiplayer(Player p1,Player p2);
    
    //inline access for gameCount
    //int getGameCount() const {return gameCount;}
    
    //Overloaded operators
    void operator=(const Board&);
    //Friend Function
    friend ostream &operator<<(ostream &,Board&);
private:
    char **data;
    int rows;
    int cols;
    bool gameOver = false;
    char placeHolder = '-';
    CPU *boardCPU; // Aggregation. Board class contains the CPU class
    Player p1;
    Player p2;
    
   // static int gameCount; // Static member variable that counts how many games have been played
    
    //Test Obj Array
     AbsPlayer** playerArr = new AbsPlayer*[2];
};

//Definition of the static member function is written outside of the class
//int Board::gameCount = 0;

#endif /* BOARD_H */

