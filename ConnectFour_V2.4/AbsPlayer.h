

/* 
 * File:   AbsPlayer.h
 * Author: Michael
 *
 * Created on May 22, 2018, 5:49 PM
 */

#ifndef ABSPLAYER_H
#define ABSPLAYER_H

#include <string>
using namespace std;

class AbsPlayer {
public:
    //Pure virtual function
    virtual string getName() = 0;
    
protected:
    string name;

};

#endif /* ABSPLAYER_H */

