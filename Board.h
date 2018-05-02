#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include <vector>
#include <SFML/Graphics.hpp>
#include "Square.h"
#include "Player.h"


using namespace std;
using namespace sf;

// class pour créer le plateau en lui même
class Board{

private:
    // vecteur qui va contenir toutes les cases du plateau
    vector<Square*> tab;
    vector<Square*>SquareSelect;
    // vecteur qui va contenir les hexagones pour chaque case
    //(on peut retrouver l'hexagone d'une case car ils sont rangés dans le même ordre sur chaque vecteur)
    vector<CircleShape> graphics_board;
    vector<CardBoard*> allcard;
    vector<CardBoard*> diecard;
    Player* joueur;
    int PlaySquare;
    //------------------------
    void selectsquare(int i);
    void movementpawn(int i);

public:
    // constructeur
    Board(Player* joueur);
    // destructeur
    ~Board();
    // autre méthode ou fonction
    void echo();
    void echo_case(int id);
    void liaison();
    void settower(Card* tower);
    vector<Square*> get();
    void display(RenderWindow* window);
    void collision(RenderWindow* window);
    int setallcard(CardBoard* card);
    void deselect();
    void setplayer(Player* joueur);
    vector<CardBoard*> getdie();
    void destructdiecard();
};

#endif // PLATEAU_H_INCLUDED
