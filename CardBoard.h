#ifndef CARTEPLATEAU_H_INCLUDED
#define CARTEPLATEAU_H_INCLUDED
#include "Card.h"

using namespace std;


class CardBoard{
private:
    string type;
    string name;
    int life;
    int attaque;

public:
    CardBoard(Card* card);
    void echo();
};
#endif // CARTEPLATEAU_H_INCLUDED
