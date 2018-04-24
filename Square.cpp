#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Square.h"

using namespace std;
using namespace sf;

Square::Square(int id){

    numero = id;
    empty=true;

    // en fonction de l'id reçus on va définir cet objet, lui affecter une couleur un camp et un type
    if(id < 16){
        camp = "Joueur 1";
        if(id < 3){
            type = "Tour";
            red=188;
            green=79;
            blue=13;
        }else{
            type = "Case";
            red=0;
            green=204;
            blue=9;
        }
    }else if(id < 34){
        camp = "Neutre";
        if((id  == 22) || (id == 27)){
            type = "Puit de mana";
            red=5;
            green=119;
            blue=248;
        }else{
            type = "Case";
            red=240;
            green=240;
            blue=240;
        }
    }else{
        camp = "Joueur 2";
        if(id > 46){
            type = "Tour";
            red=188;
            green=79;
            blue=13;
        }else{
            type = "Case";
            red=0;
            green=204;
            blue=9;
        }
    }
}


// cette fonction retourne le vecteur contenant les adresses des cases adjacentes
vector<Square*>& Square::get(){

    return nearbySquare;
}

int Square::getnumero (){
    return numero;
}

int Square::getred (){
    return red;
}

int Square::getgreen (){
    return green;
}

int Square::getblue (){
    return blue;
}

string Square::getcamp(){
    return camp;
}

string Square::gettype(){
    return type;
}
vector<Square*> Square::getnearby(){
    return nearbySquare;
}
void Square::setpos(int x, int y){
    position.x=x;
    position.y=y;
}
void Square::setnearby(Square* square){
    nearbySquare.push_back(square);
}
void Square::setpawn(Card* card,Vector2f position){
    pawn=new CardBoard(card,position);
    empty=false;
}
CardBoard* Square::getpawn(){
    return pawn;
}
Vector2f Square::getpos(){
    cout<<"square id:"<<numero<<endl;
    cout<<"square x:"<<position.x<<endl;
    cout<<"square y:"<<position.y<<endl;
    return position;
}
