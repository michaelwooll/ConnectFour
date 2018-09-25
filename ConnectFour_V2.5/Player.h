
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


class Player:public AbsPlayer {
public:
    //Constructor
    Player(string n ="Placeholder");
    
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
    
    //Friend function for overloaded << operator
    friend ostream &operator<<(ostream &,Player&);
private:
    int wins;
    int losses;

};

#endif /* PLAYER_H */

