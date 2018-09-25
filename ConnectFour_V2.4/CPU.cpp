

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

