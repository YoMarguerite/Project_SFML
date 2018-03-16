#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include "Square.h"

using namespace std;
using namespace sf;

Emplacement::Emplacement(int id){

    numero = id;

    // en fonction de l'id reçus on va définir cet objet, lui affecter une couleur un camp et un type
    if(id < 16){
        camp = "Joueur 1";
        if(id < 3){
            type = "Tour";
            rouge=255;
            vert=100;
            bleu=0;
        }else{
            type = "Case";
            rouge=20;
            vert=255;
            bleu=30;
        }
    }else if(id < 34){
        camp = "Neutre";
        if((id  == 22) || (id == 27)){
            type = "Puit de mana";
            rouge=100;
            vert=185;
            bleu=255;
        }else{
            type = "Case";
            rouge=240;
            vert=240;
            bleu=240;
        }
    }else{
        camp = "Joueur 2";
        if(id > 46){
            type = "Tour";
            rouge=255;
            vert=100;
            bleu=0;
        }else{
            type = "Case";
            rouge=20;
            vert=255;
            bleu=30;
        }
    }
}


// cette fonction retourne le vecteur contenant les adresses des cases adjacentes
vector<Emplacement*>& Emplacement::get(){

    return proche;
}
