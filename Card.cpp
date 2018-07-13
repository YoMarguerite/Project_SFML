#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include "Card.h"

using namespace std;
using namespace sf;

//constructeur d'une carte, on définis ses stats
Card::Card(int id, Statcard* stat, int i){
    this->id = id;
    vector<string>importstat=stat->getstats(id);
    quality=importstat[1];
    name=importstat[2];
    family=importstat[3];
    mana=atoi(importstat[4].c_str());
    damage=atoi(importstat[5].c_str());
    life=atoi(importstat[6].c_str());
    movement=atoi(importstat[7].c_str());
    build=atoi(importstat[8].c_str());
    short type=atoi(importstat[9].c_str());
    if(type==0){
        this->type="Unite";
    }
    if(type==1){
        this->type="Batiment";
    }
    if(type==2){
        this->type="Sort";
    }
    dessin=stat->getimage(id);
    dessin.setSmooth(true);
    image.setTexture(dessin);
    image.setPosition(100+150*i,800);
    image.setScale(Vector2f(0.5f, 0.5f));
    select=false;
}


Card::~Card(){}

//return le sprite de la carte
Sprite Card::getimage(){
    return image;
}
//affichage de la carte
void Card::echocard(RenderWindow* window){

    window->draw(image);
}
//modification de la taille de la carte si on passe dessus
void Card::hovercard(int a, int b, Vector2f z){
    image.setPosition(a,b);
    image.setScale(z);
}
//la carte reprends sa taille normale
void Card::nothovercard(int i){
    image.setPosition(100+i*150,800);
    image.setScale(0.5,0.5);
}
//on sélectionnes ou on déselectionnes la carte
void Card::setselect(bool check){
    select=check;
}

int Card::getid(){
    return id;
}
//on récupère sa rareté
string Card::getquality(){
    return quality;
}
//on récupère son nom
string Card::getname(){
    return name;
}
//on récupère son coût en mana
int Card::getmana(){
    return mana;
}
//on récupère son type, unité, bâtiment, sort
string Card::gettype(){
    return type;
}
//on récupère le bool qui permet de dire si elle est sélectionnée ou non
bool Card::getselect(){
    return select;
}
//on récupère sa famille
string Card::getfamily(){
    return family;
}
//on récupère sa vie
int Card::getlife(){
    return life;
}
//on récupère son attaque
int Card::getdamage(){
    return damage;
}
//on récupère ses points de déplacements
int Card::getmovement(){
    return movement;
}
//on récupère son état endormie ou non
bool Card::getsleep(){
    return sleep;
}
//on récupère son temps de constu
int Card::getbuild(){
    return build;
}
