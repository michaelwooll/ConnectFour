

/* 
 * File:   Board.cpp
 * Author: Michael
 * 
 * Created on May 8, 2018, 3:23 PM
 */

#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

void clearScreen();

Board::Board(int rowIn, int colIn) {
    rows = rowIn;
    cols = colIn;
    
    data = new char*[rows]; // Dynamically Create 2D Array
    
    for(int i = 0; i < rows; i++){
        *(data + i) = new char[cols];
    }
    
    //Now fill the array with placeholder character
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            data[i][j] = placeHolder; //Placeholder character for empty slot
        }
    }
}



Board::~Board() { // Deletes dynamically created array inside of board
    for(int i = 0; i < rows; i++){
        delete []data[i];
    }
    delete []data;
}

void Board::print(){
    cout << "|0|1|2|3|4|5|6|" << endl;
    cout << "===============" << endl;
    
    for(int i = 0; i < rows; i++){
        cout << "|";
        for(int j = 0; j < cols; j++){
            cout << data[i][j] << "|";
        }
        cout << endl;
    }
    cout << "---------------" << endl << endl;
}

int Board::placePiece(int col){
    int win = 0; //initialize win flag (1 = player win and 2 = CP win)
    
    // Do some error testing to check if column is good input
    
    // Loop through specified column to find the appropriate spot
    for(int i = rows - 1; i >= 0; i--){
        if(data[i][col] == placeHolder){
            data[i][col] = 'X';
            this->print();
            win = this->checkWin();
            return win;
        }
    }
    return win;
}

int Board::placeTestPiece(int col){ //Used for testing purposes

    int win = 0; //initialize win flag (1 = player win and 2 = CP win)
    
    // Do some error testing to check if column is good input
    
    // Loop through specified column to find the appropriate spot
    for(int i = rows - 1; i >= 0; i--){
        if(data[i][col] == placeHolder){
            data[i][col] = 'O';
            this->print();
            win = this->checkWin();
            return win;
        }
    }
    return win;
}

int Board::AI(){
    int col = rand()%6; // Random number between 0-6
    int win = 0;
    for(int i = rows - 1; i>=0; i--){
        if(data[i][col] == placeHolder){
            data[i][col] = 'O';
            win = this->checkWin();
            i = 0;
        }
    }
    return win;
}

int Board::checkWin(){ //Checks for four in a row
    
    //Horizontal case
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols-3; col++){ // Only check columns that can produce four in a row
            if(data[row][col] != placeHolder){ // If data is an actual game piece (X or O)
                if(data[row][col] == data[row][col+1] && data[row][col+1] == data[row][col+2] && data[row][col+2] == data[row][col+3]){ // Check pieces horizontal to each other
                    if(data[row][col] == 'X') {return 1;} // Player is always X
                    if(data[row][col] == 'O'){return 2;} // Computer is always O
                }
            }
        }
    }
    
    //Vertical Case
    for(int row = 0; row < rows-3; row++){ // Only check rows that can produce four in a row
        for(int col = 0; col < cols; col++){
             if(data[row][col] != placeHolder){ // If data is an actual game piece (X or O)
                if(data[row][col] == data[row+1][col] && data[row+1][col] == data[row+2][col] && data[row+2][col] == data[row+3][col]){ // Check pieces vertical to each other
                    if(data[row][col] == 'X') {return 1;} // Player is always X 
                    if(data[row][col] == 'O'){return 2;} // Computer is always O
                }
            }
        }
        
    }
    
    //Left Diagonal Case
    for(int row = 0; row < rows-3; row++){ //Only check rows that can produce four in a row
        for(int col = 0; col < cols-3; col++){ //Only check columns that can produce four in a row
            if(data[row][col] != placeHolder){ // If data is an actual game piece (X or O)
                if(data[row][col] == data[row+1][col+1] && data[row+1][col+1] == data[row+2][col+2] && data[row+2][col+2] == data[row+3][col+3]){ //Check pieces in right diagonal pattern
                    if(data[row][col] == 'X'){return 1;} // Player is always X
                    if(data[row][col] == 'O'){return 2;} // Computer is always O
                }
            }
        }
    }
    
    //Right Diagonal Case
    for(int row = 0; row < rows-3; row++){ // Only check rows that can produce four in a row
        for(int col = cols-4; col < cols; col++){ // Only check columns that can produce four in a row
            if(data[row][col] != placeHolder){ //If data is an actual game piece (X or O)
                if(data[row][col] == data[row+1][col-1] && data[row+1][col-1] == data[row+2][col-2] && data[row+2][col-2] == data[row+3][col-3]){
                    if(data[row][col] == 'X'){return 1;} // Player is always X
                    if(data[row][col] == 'O'){return 2;} // Computer is always O
                }
            }
        }
    }
    return 0;
}

void Board::play(){
    int colPick;
    int win = 0;
    while(!gameOver){
        cout << "It is your turn. Choose a column to place your X (0-6)" << endl << endl;
        this->print();
        cin >> colPick;
        win = placePiece(colPick);
        if(win == 1){
            cout << "Player wins!" << endl;
            gameOver = true;
        }
        win = AI();
        if(win == 2){
            this->print();
            cout << "Computer wins!" << endl;
            gameOver=true;
        }
    }
}

void clearScreen(){
    cout << string(50,'\n');
}
