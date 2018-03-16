#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "CartePlateau.h"

using namespace std;
using namespace sf;

// class pour créer les différentes cases du plateau de manière indépendante
class Emplacement{

public:
    int numero;
    // couleur enregistrée pour chaque case
    int rouge;
    int vert;
    int bleu;
    // carte sur la case
    bool vide;
    CartePlateau carte;
    // effet sur la case
    bool mana;
    bool poison;
    // définition de la case
    string camp;
    string type;
    // case adjacente
    vector<Emplacement*> proche;

    //constructeur et autre méthode
    Emplacement(int id);
    vector<Emplacement*>& get();

};

#endif // SQUARE_H_INCLUDED
