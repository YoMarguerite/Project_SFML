#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include <vector>
#include <SFML/Graphics.hpp>
#include "Square.h"


using namespace std;
using namespace sf;

// class pour créer le plateau en lui même
class Plateau{

private:
    // vecteur qui va contenir toutes les cases du plateau
    vector<Emplacement*> tab;

    // vecteur qui va contenir les hexagones pour chaque case
    //(on peut retrouver l'hexagone d'une case car ils sont rangés dans le même ordre sur chaque vecteur)
    vector<CircleShape> plateau_graphique;

public:
    // constructeur
    Plateau();
    // destructeur
    ~Plateau();
    // autre méthode ou fonction
    void echo();
    void echo_case(int id);
    void liaison();
    vector<Emplacement*>& get();
    void afficher(RenderWindow* window);
    void collision(RenderWindow* window);

};

#endif // PLATEAU_H_INCLUDED
