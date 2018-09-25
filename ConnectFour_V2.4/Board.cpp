
/* 
 * File:   Board.cpp
 * Author: Michael
 * 
 * Created on May 8, 2018, 3:23 PM
 */

#include "Board.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h> // Sleep() function

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
    delete []playerArr;
}

//Copy constructor
Board::Board(Board& copy){
    rows = copy.rows;
    cols = copy.cols;
    data = new char*[rows]; // Dynamically Create 2D Array
    for(int i = 0; i < rows; i++){
        *(data + i) = new char[cols];
    }
    
    //Copy over 2D Array
    for(int i = 0; i < rows; i++){
        for(int j = 0; j<cols; j++){
            data[i][j] = copy.data[i][j];
        }
    }
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

int Board::placePiece(){
    int col;
    int win = 0; //initialize win flag (1 = player win and 2 = CP win)
    cout << "It is your turn. Choose a column to place your X (0-6)" << endl << endl;
   // this->print();
    cin >> col;
    
    // Do some error testing to check if column is good input
    if(isColFull(col)){
        cout << "ERROR: COLUMN IS FULL!!!!!" << endl ;
        return placePiece();
    }
    // Loop through specified column to find the appropriate spot
    for(int i = rows - 1; i >= 0; i--){
        if(data[i][col] == placeHolder){
            data[i][col] = 'X';
            //this->print();
            win = this->checkWin();
            return win;
        }
    }
    return win;
}

void Board::setDiff(){
    char diff;
    cout << "Please enter the character related to your desired difficulty: E = Easy, M = Medium, H = Hard." << endl;
    cin >> diff;
    diff = toupper(diff);
    if(diff == 'E' || diff == 'M' || diff == 'H'){
        boardCPU = new CPU(diff);
    }
    else{
        return setDiff();
    }
}


int Board::AI(){ // AI that logically places based on hierarchy of cases
   
    // This block is used strictly for UI purposes
    cout << "Computer is thinking..." << endl;
    Sleep(2000);
    clearScreen();
    // End block
    
    Board simulate; // Board used to simulate piece placement
    vector<int> indexes; // Vector used to store indexes // STL Container // 
    int win = 0; // Win flag
    int col; // Integer used to store selected column
    bool isConn; //Bool used to check if there is a valid connection for the AI
    int diff = boardCPU->getDifficulty();
    
    //Case 1: Computer wins
    for(int i = 0; i < cols; i++){ // Loop through each column
        simulate = *this; // Copying data from real game board to temporary game board
        if(!isColFull(i)){
            win = simulate.placeAIPiece(i); 
            if(win == 2){ // If AI wins from placement, then store index where this happens
               // cout << "win found at col: " << i << endl;
                indexes.push_back(i); // Stores index inside of vector
            }
        }
    }
    // Case 1: If win condition is found, it will randomly select one inside the vector
    if(indexes.size() > 0){     
        col = indexes[rand()%(indexes.size())]; // Selects random column within vectors index range   
        win = placeAIPiece(col); // Places the piece
        cout << "Computer played column " << col << endl;
        return win; // Returns outcome (win);
    }
   
    //Case 2: No win condition, check for losing condition
    for(int i = 0; i < cols; i++){
        simulate = *this; // Copying data from real game board to temporary game board
            if(!isColFull(i)){
            win = simulate.placeTestPiece(i);
            if(win == 1){ //If player can win off next turn, then store where this happens
                indexes.push_back(i); // Stores index inside of vector
            }
        }
    }
    //Case 2: If losing condition is found, randomly select one from inside the vector
    if(indexes.size()>0){
        if(rand()%diff != 0){
            col = rand()%7;
            win = placeAIPiece(col);
            cout << "Computer played column " << col << endl;
            return win;
        }
        col = indexes[rand()%(indexes.size())];
        win = placeAIPiece(col);
        cout << "Computer played column " << col << endl;        
        return win;
    }
    
    //Case 3: No win or loss condition found, check for connection
    for(int i = 0; i < cols; i++){
        simulate = *this;
        if(!isColFull(i)){
            isConn = simulate.isConnect(i);
            if(isConn){
                indexes.push_back(i);
            }
        }
    }
    //Case 3: If connections are found, randomly select on from inside the vector
     if(indexes.size()>0){
        col = indexes[rand()%(indexes.size())];
        win = placeAIPiece(col);
        cout << "Computer played column " << col << endl;
        return win;
    }
    
    //Case 4: There is no win found, block win found, or connection found. Place at random
    col = rand()%cols;
    win = placeAIPiece(col);
    cout << "Computer played column " << col << endl;
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
    Player *p1Ptr;
    p1Ptr = &this->p1;
  bool play = true;
  char playChar;
  while(playChar != 'Q'){
    //
    this->setDiff();
    playerArr[0] = this->boardCPU;
    playerArr[1] = p1Ptr;
    int colPick;
    int win = 0;
    while(!gameOver){
       // cout << "It is your turn. Choose a column to place your X (0-6)" << endl << endl;
       // this->print();
       // cin >> colPick;
        this->print();
        win = placePiece();
        clearScreen();
        //this->print();
        cout << *this; // Testing << operator overloading. Works fine
        if(win == 1){
            cout << "Player wins!" << endl;
            p1.win();
            gameOver = true;
        }
        else{
            win = AI();
        }
       // this->print();
        if(win == 2){
            p1.loss();
            this->print();
            cout << "Computer wins!" << endl;
            gameOver=true;
        }
    }
    p1.displayRec();
    cout << endl <<  "Enter 'Q' to quit or enter anything else to play again" << endl;
    cin >> playChar;
    playChar = toupper(playChar);
    gameOver = false;
    this->reset(); //Sets current board to a new board to start game over
  }
  
  //delete p1Ptr;
}

void Board::start(){
    string username, fileName;
    fstream in;
    
    cout << "Welcome to Connect Four!" << endl << endl;
    cout << "Enter new username to create or enter a old username to load" << endl
         << "(If you are creating a new user you the username must be greater than 3 characters in length): ";
    cin >> username;
    Player p1("Placeholder");
    
    //Exception handling
    try{
        Player p1(username);
    }
    catch(Player::smallSize){
        cout << "Error: Username must be 4 characters or longer" << endl;
        cout << endl << endl << endl;
        return start();
    }

    // Create file path
    fileName = "./Players/";
    fileName += username;
    fileName += ".bin"; 
    
    in.open(fileName,ios::in | ios::binary);
    if(!in.is_open()){
        cout << "Player not found in files. Creating new user..." << endl;
        Player createdPlayer(username);
        p1 = createdPlayer;
        p1.save();
    }
    else{
        cout << "User found. Loading in player file." << endl;
        Player loadedPlayer(username);
        loadedPlayer.load();
        p1 = loadedPlayer;
    }
    
    cout << endl << endl;
    this->setPlayer(p1);
    play();
    
    cout << endl << endl;
    this->p1.save();
    
      
}

bool Board::isColFull(int col){ 
    if(data[0][col] != placeHolder){ //If the top piece is not the placeholder piece the column is full
        return true;
    }
    else{
        return false;
    }
}

//AI Helper Functions

int Board::placeAIPiece(int col){ //Places 'O', the piece correlated with the computer at specified column
    int win = 0; //initialize win flag (1 = player win and 2 = CP win)
    
    // Do some error testing to check if column is good input
    
    // Loop through specified column to find the appropriate spot
    for(int i = rows - 1; i >= 0; i--){
        if(data[i][col] == placeHolder){
            data[i][col] = 'O';
           // this->print();
            win = this->checkWin();
            return win;
        }
    }
    return win;
}

int Board::placeTestPiece(int col){ // Used to simulate placement for AI
    int win = 0; //initialize win flag (1 = player win and 2 = CP win)
    
    // Do some error testing to check if column is good input
    
    // Loop through specified column to find the appropriate spot
    for(int i = rows - 1; i >= 0; i--){
        if(data[i][col] == placeHolder){
            data[i][col] = 'X';
            //this->print();
            win = this->checkWin();
            return win;
        }
    }
    return win;
}


bool Board::isConnect(int col){ // Function used to check if placing a piece makes a connection for AI
    int row; // Variable to hold the row value of the top piece
    if(isColFull(col)){ // Returns false if the column is full
        return false;
    }
    
    for(int i = 0; i < rows; i++){
        if(data[i][col] != placeHolder){
            row = i-1;
        }
        else{
            row = 5;
        }
    }
    if(col == 0 && row !=5){
        if(data[row][col+1] == 'O' ||  data[row-1][col+1] == 'O' || data[row+1][col] == 'O'|| data[row+1][col+1] == 'O'){
            return true;
        }
        else{
            return false;
        }
    }
    
    else if(col == 0 && row == 5){
        if(data[row][col+1] == 'O' || data[row-1][col+1] == 'O'){
            return true;
        }
        else{
            return false;
        }
    }
    
    else if(col == 6 && row != 5){
        if(data[row][col-1] == 'O' ||  data[row-1][col-1] == 'O' || data[row+1][col-1] == 'O' || data[row+1][col] == 'O'){
            return true;
        }
        else{
            return false;
        } 
    }
    
    else if(col == 6 && row ==5){
        if(data[row][col-1] == 'O' || data[row-1][col-1] == 'O'){
            return true;
        }
        else{
            return false;
        }
    }
    
    else if (row != 5){
        if(data[row][col+1] == 'O' ||  data[row-1][col+1] == 'O' || data[row+1][col] == 'O'|| data[row+1][col+1] == 'O' || data[row-1][col] == 'O' || data[row][col-1] == 'O' || data[row-1][col-1] == 'O' || data[row+1][col-1] == 'O'){
            return true;
        }
        else{
            return false;
        }
    }
    
    else{
        if(data[row-1][col] == 'O' || data[row][col-1] == 'O' || data[row][col+1] == 'O' || data[row-1][col+1] == 'O' || data[row-1][col+1] == 'O'){
            return true;
        }
        return false;
    }


    
}

void Board::reset(){
    for(int i = 0; i < rows; i++){
        delete []data[i];
    }
    delete []data;
    
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

//Clear Screen
void clearScreen(){
    cout << string(50,'\n');
}



//Overloaded operators
void Board::operator =(const Board &right){
    rows = right.rows;
    cols = right.cols;
    
    data = new char*[rows]; // Dynamically Create 2D Array
    for(int i = 0; i < rows; i++){
        *(data + i) = new char[cols];
    }
    
    //Copy over 2D Array
    for(int i = 0; i < rows; i++){
        for(int j = 0; j<cols; j++){
            data[i][j] = right.data[i][j];
        }
    }
}


// Friend function to overload << operator
ostream &operator <<(ostream &out,Board &obj){
    out << "|0|1|2|3|4|5|6|" << endl;
    out << "===============" << endl;
    
    for(int i = 0; i < obj.rows; i++){
        out << "|";
        for(int j = 0; j < obj.cols; j++){
            out << obj.data[i][j] << "|";
        }
        out << endl;
    }
    out << "---------------" << endl << endl;
    
    return out;
}
