#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
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
    bool select;
    string family;
    int life;
    int damage;
    int movement;
    bool sleep;
    int build;

    public:
    Card(int id, Statcard* stat, int i);
    void importStats();
    Sprite getimage();
    void echocard(RenderWindow* window);
    void hovercard(int a, int b, Vector2f z);
    void nothovercard(int i);
    void setselect(bool check);
    bool getselect();
    string getname();

};

#endif // CARD_H_INCLUDED
