#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "Card.h"

using namespace std;
using namespace sf;

// class pour cr�er les diff�rentes cases du plateau de mani�re ind�pendante
class Square{
private:
    int numero;
    // couleur enregistr�e pour chaque case
    int red;
    int green;
    int blue;
    // carte sur la case
    bool empty;
    Unity* pawn;
    Building* build;
    // effet sur la case
    bool mana;
    bool poison;
    // d�finition de la case
    string camp;

public:

    string type;
    // case adjacente
    vector<Square*> nearbySquare;

    //constructeur et autre m�thode
    Square(int id);
    vector<Square*>& get();
    int getnumero();
    int getred();
    int getgreen();
    int getblue();
    string getcamp();

};

#endif // SQUARE_H_INCLUDED
