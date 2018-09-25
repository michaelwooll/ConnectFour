/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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

