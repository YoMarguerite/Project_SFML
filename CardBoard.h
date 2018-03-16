#ifndef CARTEPLATEAU_H_INCLUDED
#define CARTEPLATEAU_H_INCLUDED

using namespace std;


class CardBoard{

public:
    string type;
    string name;
    int life;
    int attaque;

    CardBoard();
    void echo();
};
#endif // CARTEPLATEAU_H_INCLUDED
