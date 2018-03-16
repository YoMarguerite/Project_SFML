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

    // en fonction de l'id reçus on va définir cet objet, lui affecter une couleur un camp et un type
    if(id < 16){
        camp = "Joueur 1";
        if(id < 3){
            type = "Tour";
            red=255;
            green=100;
            blue=0;
        }else{
            type = "Case";
            red=20;
            green=255;
            blue=30;
        }
    }else if(id < 34){
        camp = "Neutre";
        if((id  == 22) || (id == 27)){
            type = "Puit de mana";
            red=100;
            green=185;
            blue=255;
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
            red=255;
            green=100;
            blue=0;
        }else{
            type = "Case";
            red=20;
            green=255;
            blue=30;
        }
    }
}


// cette fonction retourne le vecteur contenant les adresses des cases adjacentes
vector<Square*>& Square::get(){

    return nearbySquare;
}
