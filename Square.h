#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include "Card.h"
#include "CardBoard.h"

using namespace std;
using namespace sf;

// class pour cr�er les diff�rentes cases du plateau de mani�re ind�pendante
class Square{
private:
    int numero;
    Vector2f position;
    // couleur enregistr�e pour chaque case
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
    // d�finition de la case
    string camp;
    string type;
    // case adjacente
    vector<Square*> nearbySquare;
public:
    //constructeur et autre m�thode
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
