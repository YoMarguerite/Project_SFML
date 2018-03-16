#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "CartePlateau.h"

using namespace std;
using namespace sf;

// class pour cr�er les diff�rentes cases du plateau de mani�re ind�pendante
class Emplacement{

public:
    int numero;
    // couleur enregistr�e pour chaque case
    int rouge;
    int vert;
    int bleu;
    // carte sur la case
    bool vide;
    CartePlateau carte;
    // effet sur la case
    bool mana;
    bool poison;
    // d�finition de la case
    string camp;
    string type;
    // case adjacente
    vector<Emplacement*> proche;

    //constructeur et autre m�thode
    Emplacement(int id);
    vector<Emplacement*>& get();

};

#endif // SQUARE_H_INCLUDED
