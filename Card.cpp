#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Card.h"

using namespace std;
using namespace sf;


Card::Card(int id, Statcard* stat, int i){
    this->id = id;
    vector<string>importstat=stat->getstats(id);
    quality=importstat[1];
    name=importstat[2];
    mana=atoi(importstat[4].c_str());
    type=atoi(importstat[9].c_str());
    dessin=stat->getimage(id);
    dessin.setSmooth(true);
    image.setTexture(dessin);
    image.setPosition(300+150*i,800);
    image.setScale(Vector2f(0.5f, 0.5f));
    select=false;
}

void Card::importStats(){

}

Sprite Card::getimage(){
    return image;
}

void Card::echocard(RenderWindow* window){

    window->draw(image);
}

void Card::hovercard(int a, int b, Vector2f z){
    image.setPosition(a,b);
    image.setScale(z);
}

void Card::nothovercard(int i){
    image.setPosition(300+i*150,800);
    image.setScale(0.5,0.5);
}
void Card::setselect(bool check){
    select=check;
}

string Card::getname(){
    return name;
}
