/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: Michael
 *
 * Created on May 15, 2018, 6:29 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "AbsPlayer.h"
using namespace std;


class Player:AbsPlayer {
public:
    //Constructor
    Player(string);
    
    //Getter Functions
    string getName(){return name;}
    int getWins(){return wins;}
    int getLosses(){return losses;}
    
    //Mutators
    void win(){wins++;}
    void loss(){losses++;}
    
    //Binary save and load functions
    void load();
    void save();
    
    //Display record
    void displayRec(); // Returns the name, wins, and losses of the player.
    
    //Exception class
    class smallSize {}; // This exception will be thrown if the player name is less than 4 characters.
private:
    int wins;
    int losses;

};

#endif /* PLAYER_H */

