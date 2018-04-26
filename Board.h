#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include <vector>
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "Player.h"


using namespace std;
using namespace sf;

// class pour cr�er le plateau en lui m�me
class Board{

private:
    // vecteur qui va contenir toutes les cases du plateau
    vector<Square*> tab;

    // vecteur qui va contenir les hexagones pour chaque case
    //(on peut retrouver l'hexagone d'une case car ils sont rang�s dans le m�me ordre sur chaque vecteur)
    vector<CircleShape> graphics_board;
    vector<CardBoard*> allcard;
    Player* joueur1;

public:
    // constructeur
    Board(Player* joueur);
    // destructeur
    ~Board();
    // autre m�thode ou fonction
    void echo();
    void echo_case(int id);
    void liaison();
    vector<Square*>& get();
    void display(RenderWindow* window);
    void collision(RenderWindow* window);
    void setallcard(CardBoard* card);
    void deselect();
};

#endif // PLATEAU_H_INCLUDED
