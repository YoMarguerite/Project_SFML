#include <iostream>
#include <SFML/Graphics.hpp>
#include "CardBoard.h"

using namespace std;
using namespace sf;


CardBoard::CardBoard(Card* card,Vector2f position){
    quality=card->getquality();
    name=card->getname();
    family=card->getfamily();
    mana=card->getmana();
    damage=card->getdamage();
    life=card->getlife();
    movement=card->getmovement();
    build=card->getbuild();
    type=card->gettype();
    if(!dessin.loadFromFile("image/piont.png")){
        cerr<<"Image introuvable"<<endl;
    }
    image.setTexture(dessin);
    image.setPosition(position.x-80,position.y+20);
}

void CardBoard::echo(){
    cout << type << endl;
    cout << name << endl;
    cout << life << endl;
    cout << damage << endl;
}

Sprite CardBoard::getimage(){
    return image;
}

