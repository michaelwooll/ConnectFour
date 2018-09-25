
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
    srand(static_cast<unsigned int>(time(0))); // Seed random generator
    
    //Variables
    int win; // Win Flag
    Board game; // Game object
    
    game.play(); // Game loop called
 

    

    return 0;
}
