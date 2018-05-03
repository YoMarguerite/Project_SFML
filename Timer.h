#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Board.h"
#include "Statcard.h"
#include "Player.h"

using namespace std;
using namespace sf;

class Timer{
private:
    Clock clock;
    Time countdown;
    Text time;
    Text joueur;
    Font font;
    // BOUTON POUR FINIR LE TOUR AVANT LA FIN DU TIMER
    Sprite endTurn;
    Texture endTurnButton;
    bool journuit;
    int nbturn;
    bool joueurcourant;
    int sec;
    int chrono;
    int verif;
    RenderWindow* window;
    Statcard* stat;
    Player* joueur1;
    Player* joueur2;
    Board* board;
public:
    Timer(Vector2f windowsize,RenderWindow* window);
    void echo(RenderWindow* window);
    void changement();
    void endturn(RenderWindow* window);
};

#endif // TIMER_H_INCLUDED
