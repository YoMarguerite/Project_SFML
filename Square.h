#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "CardBoard.h"

using namespace std;
using namespace sf;

// class pour cr�er les diff�rentes cases du plateau de mani�re ind�pendante
class Square{

public:
    int numero;
    // couleur enregistr�e pour chaque case
    int red;
    int green;
    int blue;
    // carte sur la case
    bool empty;
    CardBoard pion;
    // effet sur la case
    bool mana;
    bool poison;
    // d�finition de la case
    string camp;
    string type;
    // case adjacente
    vector<Square*> nearbySquare;

    //constructeur et autre m�thode
    Square(int id);
    vector<Square*>& get();

};

#endif // SQUARE_H_INCLUDED
