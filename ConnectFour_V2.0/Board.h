
/* 
 * File:   Board.h
 * Author: Michael Wooll
 * Board class
 * Created on May 8, 2018, 3:23 PM
 */

#ifndef BOARD_H
#define BOARD_H

class Board {
public:
    Board(int rowIn = 6, int colIn = 7); // Default to 6 rows and 7 cols (standard game)
    ~Board();
    
    void print();
    int placePiece(int); // Places the game piece for the player at specified column
    int placeTestPiece(int); //User for testing purposes
    int checkWin(); // Checks if there are 4 in a row. (Returns 1 if player won, 2 if CPU won, and 0 if no win)
    int AI(); //AI turn
    void play(); // Game loop
private:
    char **data;
    int rows;
    int cols;
    bool gameOver = false;
    char placeHolder = '-';

};

#endif /* BOARD_H */

