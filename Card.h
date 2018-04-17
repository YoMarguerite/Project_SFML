#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
<<<<<<< HEAD
#include <iostream>

using namespace std;

class Card{

private:
    int id;
    short type;         //0:unité   1:batiment  2:sort
    string name;
    short quality;      //0:commun  1:rare      2:epique    3:legendaire
    //image
    int mana;
    string effectText;

public:
    Card(int id);
=======
#include <SFML/Graphics.hpp>
#include "Statcard.h"

using namespace std;
using namespace sf;

class Card{
    //ATTRIBUTS
    private:
    int id;
    string quality;      //commun  rare   epique   legendaire
    string name;
    int mana;
    short type;         //0:unité   1:batiment  2:sort
    string effectText;
    Texture dessin;
    Sprite image;

    public:
    Card(int id, Statcard* stat);
    void importStats();
    Sprite getimage();
    void echocard(RenderWindow* window,int i);
    string getname();
>>>>>>> master

};

class Placeable : public Card {
    private:
    int family;         //id de la famille
    int life;
    int damage;
};

class Unity : public Placeable {
    private:
    int movement;
    bool sleep;
};

class Building : public Placeable{
    int build;
<<<<<<< HEAD
    bool defensive;
=======
>>>>>>> master
};

class Spell : public Card {

};


<<<<<<< HEAD

=======
>>>>>>> master
#endif // CARD_H_INCLUDED
