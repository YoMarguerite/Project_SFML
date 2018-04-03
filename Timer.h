#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace std;
using namespace sf;

class Timer{
private:
    Clock clock;
    Time countdown;
    Text text;
    Font font;
    int nbturn;
    int joueurcourant;
    int sec;
    int chrono;
    int verif;
public:
    Timer(Vector2f windowsize);
    void echo(RenderWindow* window);
};

#endif // TIMER_H_INCLUDED
