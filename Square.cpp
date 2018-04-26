#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Square.h"

using namespace std;
using namespace sf;

//constructeur des cases du plateau
Square::Square(int id){

    numero = id;
    empty=true;
    select=false;

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
// on récupère le numéro
int Square::getnumero (){
    return numero;
}
// on récupères le taux de rouge
int Square::getred (){
    return red;
}
// on récupères le taux de vert
int Square::getgreen (){
    return green;
}
// on récupères le taux de bleu
int Square::getblue (){
    return blue;
}
// on récupères le camp de la carte
string Square::getcamp(){
    return camp;
}
// on récupères son type
string Square::gettype(){
    return type;
}
//on récupères les cases adjacentes
vector<Square*> Square::getnearby(){
    return nearbySquare;
}
//on définis la position
void Square::setpos(int x, int y){
    position.x=x;
    position.y=y;
}
//on définis les cases proches
void Square::setnearby(Square* square){
    nearbySquare.push_back(square);
}
//on définis le pion sur la case
void Square::setpawn(Card* card,Vector2f position){
    pawn=new CardBoard(card,position);
    empty=false;
}
//on récupère le pion
CardBoard* Square::getpawn(){
    return pawn;
}
//on récupères la position
Vector2f Square::getpos(){
    return position;
}
//on récupères si elle est vide ou occupée
bool Square::getempty(){
    return empty;
}
//on sait si la case est sélectionnée ou non
bool Square::getselect(){
    return select;
}
//on sélectionnes la case
void Square::setselect(){
    select=true;
}
// on la déselectionnes
void Square::deselect(){
    select=false;
}
