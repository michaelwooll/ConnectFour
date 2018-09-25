
/* 
 * File:   Player.h
 * Author: Michael
 *
 * Created on May 15, 2018, 6:29 PM
 */
#include <string>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(string);
private:
    string name;
    int wins;
    int losses;

};

#endif /* PLAYER_H */

