#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Timer.h"

using namespace std;
using namespace sf;

Timer::Timer(Vector2f windowsize){
    clock.restart();
    countdown = seconds(0.01f);
    verif=0;
    chrono=61;
    if(!font.loadFromFile("font/CloisterBlack.ttf")){
        cerr<<"Fichier font 'CloisterBlack.ttf' introuvable"<<endl;
    }
    text.setString("Début");
    text.setFont(font);
    text.setCharacterSize(75);
    text.setPosition(windowsize.x/2,windowsize.y/20);
    text.setFillColor(sf::Color::White);
    Texture textureBkg;

    if (!endTurnButton.loadFromFile("image/button_endturn.png")){
        cout << "erreur";
    }
    endTurn.setTexture(endTurnButton);
    endTurn.setPosition(windowsize.x/6,windowsize.y/50);
}

void Timer::echo(RenderWindow* window){
    string str;
    if (countdown < seconds(61)){

        countdown = clock.getElapsedTime();
        sec = floor(countdown.asSeconds());

        if(sec != verif){
            chrono--;
            stringstream stream;
            stream << chrono;
            str = stream.str();
            cout << str<<endl;
            text.setString(str);
            verif = sec;
        }
    }
    window->draw(endTurn);
    window->draw(text);
}

