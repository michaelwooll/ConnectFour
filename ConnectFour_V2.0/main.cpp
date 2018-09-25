

/* 
 * File:   main.cpp
 * Author: Michael
 *
 * Created on May 8, 2018, 3:22 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Board.h"

using namespace std;

/*
 * 
 */
int main() {
    srand(static_cast<unsigned int>(time(0)));
    int win;
    Board game;
    game.play();
    
  /*  win = game.placePiece(3);
    cout << endl << "Win = " << win << endl;
    game.placeTestPiece(4);
        win = game.placePiece(4);
    cout << endl << "Win = " << win << endl;
    game.placeTestPiece(5);
    game.placeTestPiece(5);
        win = game.placePiece(5);
    cout << endl << "Win = " << win << endl;
    game.placeTestPiece(6);
    game.placeTestPiece(6);
    game.placeTestPiece(6);
        win = game.placePiece(6);
    cout << endl << "Win = " << win << endl;*/
    
    return 0;
}
