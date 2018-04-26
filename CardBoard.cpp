#include <iostream>
#include <SFML/Graphics.hpp>
#include "CardBoard.h"

using namespace std;
using namespace sf;

//constructeur d'une carte mais celle-ci plac�e en tant que pion sur le plateau
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
    if(!dessin.loadFromFile("image/board_"+name+".png")){
        cerr<<"Image introuvable"<<endl;
    }
    image.setTexture(dessin);
    image.setPosition(position.x-100,position.y+0);
}
//on affiche ses caract�ristiques
void CardBoard::echo(){
    cout << type << endl;
    cout << name << endl;
    cout << life << endl;
    cout << damage << endl;
}
// on r�cup�re son sprite
Sprite CardBoard::getimage(){
    return image;
}
//on r�cup�re ses points de d�placements
int CardBoard::getmovement(){
    return movement;
}
