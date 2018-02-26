#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#endif // SHAPE_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// constructeur d'hexagone

CircleShape hex(int posx, int posy){

    // taille d'un côté et nombre de points
    CircleShape hexagon(35, 6);
    // couleur et épaisseur de la bordure extérieur
    hexagon.setOutlineColor(Color(250,150,100));
    hexagon.setOutlineThickness(3);
    // positionnement de l'hexagone
    hexagon.setRotation(90);
    hexagon.setPosition(posx,posy);

    return hexagon;
}
