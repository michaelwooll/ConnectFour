
/* 
 * File:   main.cpp
 * Author: Michael
 *
 * Created on May 8, 2018, 3:22 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include "Board.h"
#include "Player.h"
#include "CPU.h"


using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random generator
      
    Board game;
   // game.play();
    game.start();

    
    return 0;
}


