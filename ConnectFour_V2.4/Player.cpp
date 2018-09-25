/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: Michael
 * 
 * Created on May 15, 2018, 6:29 PM
 */
#include <fstream>
#include <string>
#include <iostream>

#include "Player.h"
using namespace std;


Player::Player(string n) {
    if(n.length() >= 4){
        name = n;
        wins = 0; 
        losses = 0;
    }
    else{
        throw smallSize();
    }
}

void Player::save(){
    fstream out;
    string fileName = "./Players/";
    fileName += name;
    fileName += ".bin";
    out.open(fileName, ios::out | ios::binary);
    out.write(reinterpret_cast<char* >(&wins),sizeof(int));
    out.write(reinterpret_cast<char* >(&losses),sizeof(int));
    
}

void Player::load(){
    fstream in;
    string fileName = "./Players/";
    fileName += name;
    fileName += ".bin";
    
    in.open(fileName, ios::in | ios::binary);
    in.read(reinterpret_cast<char* >(&wins),sizeof(int));
    in.read(reinterpret_cast<char* >(&losses),sizeof(int));
}

void Player::displayRec(){
    cout << endl << name << "'s" << " RECORD" << endl;
    cout << "Wins: " << wins << endl;
    cout << "Losses: " << losses << endl;

}


// Friend function to overload << operator
ostream &operator <<(ostream &out,Player &obj){
    out << endl << obj.name << "'s" << " RECORD" << endl;
    out << "Wins: " << obj.wins << endl;
    out << "Losses: " << obj.losses << endl;
    return out;
}