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
    Texture image;
    Sprite parchemin;
    Font font;
    vector<Text> stats;
    // vecteur qui va contenir toutes les cases du plateau
    vector<Square*> tab;
    vector<Square*>SquareSelect;
    // vecteur qui va contenir les hexagones pour chaque case
    //(on peut retrouver l'hexagone d'une case car ils sont rangés dans le même ordre sur chaque vecteur)
    vector<CircleShape> graphics_board;
    vector<CardBoard*> allcard;
    vector<Player*> joueurs;
    Player* joueur;
    int PlaySquare;
    bool victory;
    //------------------------
    void selectsquare(int i);
    void movementpawn(int i);

public:
    // constructeur
    Board(Player* joueur1,Player* joueur2);
    // destructeur
    ~Board();
    // autre méthode ou fonction
    void echo();
    void echo_case(int id);
    void liaison();
    vector<CardBoard*> settower(Card* tower);
    vector<Square*> get();
    void display(RenderWindow* window);
    void collision(RenderWindow* window);
    int setallcard(CardBoard* card);
    void deselect();
    void setplayer(Player* joueur);
    bool getvictory();
};

#endif // PLATEAU_H_INCLUDED
