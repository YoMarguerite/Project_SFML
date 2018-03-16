#ifndef CARTEPLATEAU_H_INCLUDED
#define CARTEPLATEAU_H_INCLUDED
#include <string>


using namespace std;


class CartePlateau{

public:
    string type;
    string nom;
    int vie;
    int attaque;

    CartePlateau();
    void echo();
};
#endif // CARTEPLATEAU_H_INCLUDED
