#ifndef CARTEPLATEAU_H_INCLUDED
#define CARTEPLATEAU_H_INCLUDED
#include "Card.h"

using namespace std;


class CardBoard{
private:
    string quality;
    string name;
    int mana;
    short type;
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
    CardBoard(Card* card,Vector2f position);
    void echo();
    Sprite getimage();
};
#endif // CARTEPLATEAU_H_INCLUDED
