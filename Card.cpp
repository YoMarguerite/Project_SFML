#include <iostream>
#include "Card.h"

using namespace std;


    Card::Card(int id){
        this->id = id;
        importStats();


    }

    void Card::importStats(){

    }

    void Card::beginturn() {

    }

    void Card::endturn() {

    }

    //void attack() {
    //
    //}

    void Card::kill() {

    }

    void Card::ishurt() {

    }

    void Card::isput() {

    }

    void Card::isdead() {

    }

    void Card::daybegin() { //Si il fait jour, ex�cuter quand la carte est pos�e. (Pour un effet de jour)

    }

    void Card::nightbegin() { //Si il fait nuit, ex�cuter quand la carte est pos�e. (Pour un effet de nuit)

    }


    //-----------------

    void Card::fight() {

    }

    void Card::move() {

    }

    void Card::testId() {
        cout << id << endl;
    }

