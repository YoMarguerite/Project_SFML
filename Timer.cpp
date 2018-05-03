#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Timer.h"

using namespace std;
using namespace sf;


//constructeur du timer

Timer::Timer(Vector2f windowsize,RenderWindow* window){
    this->window=window;
    stat=new Statcard;
    joueur1=new Player(stat,"Joueur 1");
    joueur2=new Player(stat,"Joueur 2");
    board=new Board(joueur1);
    board->liaison();
    board->settower(new Card(0,stat,0));
    joueur1->addCardHand();
    clock.restart();
    countdown = seconds(0.01f);
    verif=0;
    chrono=61;
    joueurcourant=true;
    nbturn=1;
    journuit=true;
    if(!font.loadFromFile("font/CloisterBlack.ttf")){
        cerr<<"Fichier font 'CloisterBlack.ttf' introuvable"<<endl;
    }
    time.setString("D�but");
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

//affichage du timer

void Timer::echo(RenderWindow* window){
    board->display(window);
    board->collision(window);
    if(Mouse::isButtonPressed(Mouse::Right)){
        board->deselect();
    }
    if(joueurcourant){
        joueur1->echoHand(window);
        joueur1->stockMana(window);
    }else{
        joueur2->echoHand(window);
        joueur2->stockMana(window);
    }

    string str;
    if (countdown < seconds(61)){

        countdown = clock.getElapsedTime();
        sec = floor(countdown.asSeconds());

        if(sec != verif){
            chrono--;
            stringstream stream;
            stream << chrono;
            str = stream.str();
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

// M�thode de changement de tour

void Timer::changement(){
    nbturn++;

    verif=0;
    chrono=61;
    clock.restart();
    countdown=clock.getElapsedTime();
    board->deselect();
    vector<CardBoard*>diecard=board->getdie();
    if(joueurcourant==true){
        for(unsigned int i=0;i<diecard.size();i++){
            joueur1->addCardDiscard(diecard[i]->getid());
            for(unsigned int j=0;j<joueur2->getplaced().size();i++){
                if(diecard[i]==joueur2->getplaced()[j]){
                    joueur2->destruct(j);
                }
            }
        }
        joueurcourant=false;
        joueur.setString("Joueur 2");
        joueur1->switchActive(false);
        joueur2->switchActive(true);
        board->setplayer(joueur2);
    }else{
        for(unsigned int i=0;i<diecard.size();i++){
            joueur2->addCardDiscard(diecard[i]->getid());
            for(unsigned int j=0;j<joueur1->getplaced().size();i++){
                if(diecard[i]==joueur1->getplaced()[j]){
                    joueur1->destruct(j);
                }
            }
        }
        joueurcourant=true;
        joueur.setString("Joueur 1");
        joueur1->switchActive(true);
        joueur2->switchActive(false);
        board->setplayer(joueur1);
    }
}
// M�thode de fin de tour
void Timer::endturn(RenderWindow* window){
    Vector2i position_mouse = Mouse::getPosition(*window);
    if(endTurn.getGlobalBounds().contains(position_mouse.x,position_mouse.y)){
            // on change sa couleur
            endTurn.setColor(Color(150,150,150));
            // si on clique la fen�tre se ferme
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
