#include <iostream>
#include "CardBoard.h"

using namespace std;


CardBoard::CardBoard(Card* card){
    type="Unité";
    name="Gobelin";
    life=3;
    attaque=3;
}

void CardBoard::echo(){
    cout << type << endl;
    cout << name << endl;
    cout << life << endl;
    cout << attaque << endl;
}

