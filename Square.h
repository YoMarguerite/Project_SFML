#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "CardBoard.h"

using namespace std;
using namespace sf;

// class pour créer les différentes cases du plateau de manière indépendante
class Square{

public:
    int numero;
    // couleur enregistrée pour chaque case
    int red;
    int green;
    int blue;
    // carte sur la case
    bool empty;
    CardBoard pion;
    // effet sur la case
    bool mana;
    bool poison;
    // définition de la case
    string camp;
    string type;
    // case adjacente
    vector<Square*> nearbySquare;

    //constructeur et autre méthode
    Square(int id);
    vector<Square*>& get();

};

#endif // SQUARE_H_INCLUDED
