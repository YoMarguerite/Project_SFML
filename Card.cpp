#include <iostream>
<<<<<<< HEAD
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
=======
#include <SFML/Graphics.hpp>
>>>>>>> master
#include <string>
#include "Card.h"

using namespace std;
<<<<<<< HEAD

Card::Card(int id) {
        this->id = id;
        //importStats();
}

void importStats(){

    }

=======
using namespace sf;


Card::Card(int id, Statcard* stat){
    this->id = id;
    vector<string>importstat=stat->getstats(id);
    quality=importstat[1];
    name=importstat[2];
    mana=atoi(importstat[4].c_str());
    type=atoi(importstat[9].c_str());
    dessin=stat->getimage(id);
    dessin.setSmooth(true);
    image.setTexture(dessin);
    image.setPosition(300,800);
    image.setScale(sf::Vector2f(0.5f, 0.5f));
}

void Card::importStats(){

}

Sprite Card::getimage(){
    return image;
}

void Card::echocard(RenderWindow* window,int i){
    image.setPosition(300+i*150,800);
    window->draw(image);
}
string Card::getname(){
    return name;
}
>>>>>>> master
