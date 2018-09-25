
/* 
 * File:   CPU.cpp
 * Author: Michael
 * 
 * Created on May 22, 2018, 6:16 PM
 */

#include "CPU.h"

CPU::CPU(char n) {
    difficulty = n;
}

int CPU::getDifficulty(){
    if(difficulty == 'E'){
        return 5;
    }
    if(difficulty == 'M'){
        return 3;
    }
    if(difficulty == 'H'){
        return 1;
    }
}

