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
    joueurcourant=1;
    nbturn=1;
    if(!font.loadFromFile("font/CloisterBlack.ttf")){
        cerr<<"Fichier font 'CloisterBlack.ttf' introuvable"<<endl;
    }
    time.setString("Début");
    time.setFont(font);
    time.setCharacterSize(75);
    time.setPosition(windowsize.x/2,windowsize.y/20);
    time.setFillColor(sf::Color::White);
    joueur.setString("Joueur 1");
    joueur.setFont(font);
    joueur.setCharacterSize(50);
    joueur.setPosition(windowsize.x/50,windowsize.y/50);
    joueur.setFillColor(sf::Color::White);

    if (!endTurnButton.loadFromFile("image/button_endturn.png")){
        cerr << "erreur";
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
            time.setString(str);
            verif = sec;
        }
    }else{
        changement();
    }
    window->draw(endTurn);
    window->draw(time);
    window->draw(joueur);
}

void Timer::changement(){
    nbturn++;
    verif=0;
    chrono=61;
    clock.restart();
    countdown=clock.getElapsedTime();
    if(joueurcourant==1){
        joueurcourant++;
        joueur.setString("Joueur 2");
    }else{
        joueurcourant--;
        cout<<"joueur"<<joueurcourant<<endl;
        joueur.setString("Joueur 1");
    }
}

void Timer::endturn(RenderWindow* window){
    Vector2i position_mouse = Mouse::getPosition(*window);
    if(endTurn.getGlobalBounds().contains(position_mouse.x,position_mouse.y)){
            // on change sa couleur
            endTurn.setColor(Color(150,150,150));
            // si on clique la fenêtre se ferme
            if(Mouse::isButtonPressed(Mouse::Left)){
                while(Mouse::isButtonPressed(Mouse::Left)){

                }
                changement();
            }
        }else{
            // sinon le bouton reprend sa couleur
            endTurn.setColor(Color(255,255,255));
        }
}
