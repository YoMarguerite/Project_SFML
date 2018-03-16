#include <iostream>
#include "CartePlateau.h"

using namespace std;


CartePlateau::CartePlateau(){
    type="Unité";
    nom="Gobelin";
    vie=3;
    attaque=3;
}

void CartePlateau::echo(){
    cout << type << endl;
    cout << nom << endl;
    cout << vie << endl;
    cout << attaque << endl;
}

