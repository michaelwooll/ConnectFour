
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

void readDirections();
int main() {
    //Flag for directions
    char dir;
    int gameType = 0;
    srand(static_cast<unsigned int>(time(0))); // Seed random generator
    
    //Prompt user to see if they want to read directions for the game
    cout << "Would you like to read the directions for Connect Four? (Y or N)" << endl;
    cin >> dir;
    dir = toupper(dir);
    if(dir == 'Y'){
        readDirections();
    }
    
    //Instantiate game object
    Board game;
    
    //Ask user what type of game mode they would want to play
    // Either play against AI or play against another user on the same machine
    
    cout << endl << "Would you like to play against the computer or would you like to play against another player";
    cout << "on the same machine?" << endl;
    cout << "Enter 1 to play against the computer and enter 2 to play against a friend." << endl;
    
    cin >> gameType;
    
    //Gametype 1 = AI game
    if(gameType == 1){
        game.start();
    }
    
    //Gametype 2 = VS friend
    else if(gameType ==2){
        game.multiplayer();
    }
    
    // Else, Error and exit
    else{
        cout << "invalid input" << endl;
        return 0;
    }

    return 0;
}

//Function used to print out directions for the game
void readDirections(){
    
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Directions" << endl << endl;
    cout << endl << "Object of the game: " << endl;
    cout << "To win Connect Four you must be the first player to get four of your ";
    cout << "game pieces in a row either horizontally, vertically or diagonally." << endl << endl;
    cout << "There are 3 different difficulties easy, medium, or hard which will determine how difficult the computer is." << endl;
    cout << "Your game pieces are the character 'X' while the CPU's game pieces are the character 'O'" << endl;
    cout << endl << "You will be asked to create a username which will be used to identify you as well as save your win/loss record" << endl;
    cout << "The username MUST be at least four characters long or you will be asked to choose a different username" << endl << endl;
    cout << "While playing you will be asked to pick a column (0-6) to place your pieces. Choose wisely!" << endl << endl;
    cout << "Good luck and have fun!" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl << endl;
   
}
