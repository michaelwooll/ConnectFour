/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CPU.h
 * Author: Michael
 *
 * Created on May 22, 2018, 6:16 PM
 */

#ifndef CPU_H
#define CPU_H

#include <string>
#include "AbsPlayer.h"

using namespace std;

class CPU:public AbsPlayer {
public:
    // Constructor
    CPU(char n = 'E');
    
    //Getter
    int getDifficulty();
    string getName(){return "Computer";}
private:
    char difficulty; //  [Easy,Medium,Hard]
};

#endif /* CPU_H */

