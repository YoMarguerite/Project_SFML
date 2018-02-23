#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#endif // SHAPE_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

CircleShape hex(int posx, int posy, int rouge, int vert, int bleu){
    CircleShape hexagon(35, 6);
    hexagon.setFillColor(Color(rouge,vert,bleu));
    hexagon.setOutlineColor(Color(250,150,100));
    hexagon.setOutlineThickness(3);
    hexagon.setRotation(90);
    hexagon.setPosition(posx,posy);

    return hexagon;
}
