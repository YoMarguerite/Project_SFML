#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "Card.h"
#include "CardBoard.h"

using namespace std;
using namespace sf;

// class pour créer les différentes cases du plateau de manière indépendante
class Square{
private:
    int numero;
    Vector2f position;
    // couleur enregistrée pour chaque case
    int red;
    int green;
    int blue;
    // carte sur la case
    bool empty;
    bool select;
    CardBoard* pawn;
    // effet sur la case
    bool mana;
    bool poison;
    // définition de la case
    string camp;
    string type;
    // case adjacente
    vector<Square*> nearbySquare;
public:
    //constructeur et autre méthode
    Square(int id);
    vector<Square*>& get();
    bool getempty();
    int getnumero();
    int getred();
    int getgreen();
    int getblue();
    string getcamp();
    string gettype();
    vector<Square*> getnearby();
    bool getselect();
    void setpos(int x, int y);
    void setnearby(Square* tab);
    void setpawn(Card* card,Vector2f position);
    void setselect();
    void deselect();
    CardBoard* getpawn();
    Vector2f getpos();
};

#endif // SQUARE_H_INCLUDED
