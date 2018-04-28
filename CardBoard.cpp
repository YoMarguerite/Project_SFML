#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "CardBoard.h"

using namespace std;
using namespace sf;

//constructeur d'une carte mais celle-ci placée en tant que pion sur le plateau
CardBoard::CardBoard(Card* card,Vector2f position,string camp){
    this->camp=camp;
    quality=card->getquality();
    name=card->getname();
    family=card->getfamily();
    mana=card->getmana();
    damage=card->getdamage();
    life=card->getlife();
    movement=card->getmovement();
    lim_move=movement;
    build=card->getbuild();
    type=card->gettype();
    id=card->getid();
    lim_coup=1;
    nbcoup=1;
    if(!dessin.loadFromFile("image/board_"+name+".png")){
        cerr<<"Image introuvable"<<endl;
    }
    image.setTexture(dessin);
    image.setPosition(position.x-100,position.y+0);
    if(!font.loadFromFile("font/CloisterBlack.ttf")){
        cerr<<"Fichier font 'CloisterBlack.ttf' introuvable"<<endl;
    }
    stringstream convertvie;
    convertvie<<life;
    Vie.setString(convertvie.str());
    Vie.setFont(font);
    Vie.setCharacterSize(30);
    Vie.setPosition(position.x-26,position.y+63);
    Vie.setFillColor(sf::Color::Black);
    stringstream convertdamage;
    convertdamage<<damage;
    Attaque.setString(convertdamage.str());
    Attaque.setFont(font);
    Attaque.setCharacterSize(30);
    Attaque.setPosition(position.x-85,position.y+63);
    Attaque.setFillColor(sf::Color::Black);
    stringstream convertmove;
    convertmove<<lim_move;
    Moving.setString(convertmove.str());
    Moving.setFont(font);
    Moving.setCharacterSize(30);
    Moving.setPosition(position.x-55,position.y-5);
    Moving.setFillColor(sf::Color::Black);

}
//on affiche ses caractéristiques
void CardBoard::echo(){
    cout << type << endl;
    cout << name << endl;
    cout << life << endl;
    cout << damage << endl;
}
// on récupère son sprite
Sprite CardBoard::getimage(){
    return image;
}

Text CardBoard::getvie(){
    return Vie;
}

Text CardBoard::getattaque(){
    return Attaque;
}

Text CardBoard::getmoving(){
    return Moving;
}

int CardBoard::getid(){
    return id;
}

int CardBoard::getmovement(){
    return movement;
}

int CardBoard::getdamage(){
    return damage;
}

int CardBoard::getcoup(){
    return nbcoup;
}

int CardBoard::getplace(){
    return place;
}

void CardBoard::setplace(int i){
    place=i;
}

void CardBoard::setmovement(){
    movement--;
}

void CardBoard::setcoup(){
    nbcoup--;
}

void CardBoard::resetstat(){
    movement=lim_move;
    nbcoup=lim_coup;
}

void CardBoard::setposition(Vector2f position){
    image.setPosition(position.x-100,position.y+0);
    Moving.setPosition(position.x-55,position.y-5);
    Attaque.setPosition(position.x-85,position.y+63);
    Vie.setPosition(position.x-26,position.y+63);
}

string CardBoard::getcamp(){
    return camp;
}

bool CardBoard::takedamage(CardBoard* opponent){
    if(life>0){
        life-=opponent->getdamage();
        opponent->setcoup();
        stringstream convertvie;
        convertvie<<life;
        Vie.setString(convertvie.str());
        if(life<=0){
            return true;
        }else{
            return false;
        }
    }else{return false;}
}
