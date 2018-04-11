#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Card.h"

using namespace std;
using namespace sf;


Card::Card(int id, Statcard* stat){
    this->id = id;
    vector<string>importstat=stat->getstats(id);
    quality=importstat[1];
    name=importstat[2];
    mana=atoi(importstat[4].c_str());
    type=atoi(importstat[9].c_str());
    image.setTexture(stat->getimage(id));
}

void Card::importStats(){

}

