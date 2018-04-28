#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Timer.h"
#include "Console.h"
#include "Statcard.h"
#include "Menu.h"


using namespace std;
using namespace sf;

bool sprite_mouse(RenderWindow* window,Vector2i position_mouse, Sprite sprite){
return sprite.getGlobalBounds().contains(position_mouse.x,position_mouse.y);
}

// fonction contenant la collision avec le bouton exit
void game(RenderWindow* window, Sprite exit, int* interface){
    Vector2i position_mouse=Mouse::getPosition(*window);
    // si le bouton quitter contient la souris
    if(sprite_mouse(window,position_mouse,exit)){
        // on change sa couleur
        exit.setColor(Color(150,150,150));
        // si on clique la fen�tre se ferme
        if(Mouse::isButtonPressed(Mouse::Left)){
             *interface=1;
        }
    }else{
        // sinon le bouton reprend sa couleur
        exit.setColor(Color(255,255,255));

    }
    // on dessine le bouton jouer et quitter sur la fen�tre
    window->draw(exit);
 }

int main()
{
    //on d�finit la taille de la fen�tre
    // Taille de la fen�tre
    Vector2f windowsize;
    windowsize.x=1600;
    windowsize.y=1000;

    // fen�tre principale avec sa taille et son nom
    RenderWindow window(VideoMode(windowsize.x,windowsize.y), "LES TOURS");
    //on d�clare une console, class en cour de d�veloppement
    Console console;
    //on d�clare un menu
    Menu menu(windowsize);
    // variable d�finissant si on est sur le menu ou dans une partie
    int interface = 1;
    // limite les fps pour ne pas faire surchauffer la carte graphique (�a peut vraiment crasher sinon)
    window.setFramerateLimit(60);
    //cr�ation de l'instance stat qui contiendra les stats de toutes les cartes, on importe les stats qu'une seule fois
    //cr�ation du timer
    Timer chrono(windowsize,&window);

    //    Chargement de la texture pour le background

    Texture textureBkg2;
    if (!textureBkg2.loadFromFile("image/backgroundGame.jpg")){
        cout << "erreur";
    }

    //    Chargement de la texture pour le background
    Sprite bckg2;

    //on donne cette texture aux sprites, et on leur donne des coordonn�es
    bckg2.setTexture(textureBkg2);
    bckg2.setPosition(0,0);

    // ------------------- QUITTER LE JEU EN COURS DE PARTIE -------------------

    Sprite exit;
    Texture exitGame;
	if (!exitGame.loadFromFile("image/button_exit.png")) {
		cout << "erreur";
	}
 	exit.setTexture(exitGame);
 	exit.setPosition((windowsize.x)-(windowsize.x)/17,windowsize.x/90);

    Music menuMusic;
    if (!menuMusic.openFromFile("music/menu.ogg")){
        cout<<"erreur";
    }

    Music gameMusic;
    if (!gameMusic.openFromFile("music/game.ogg")){
        cout<<"erreur";
    }

 	bool activeMenuMusic = true;
 	bool activeGameMusic = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                 window.close();
            }
        }
        window.clear();
        // on v�rifie sur qu'elle interface on est menu ou en jeu
        if(interface == 1){
            // execution du menu
            if (activeMenuMusic) {
            gameMusic.stop();
            menuMusic.play();
            activeMenuMusic = false;
            activeGameMusic = true;
            }
            menu.display(&window,&interface);
        }else{
            if (activeGameMusic) {
            menuMusic.stop();
            gameMusic.play();
            activeMenuMusic = true;
            activeGameMusic = false;
            }
            window.draw(bckg2);
             // execution du jeu
            game(&window,exit,&interface);
            chrono.echo(&window);
            chrono.endturn(&window);
        }
        //affichage sur la fen�tre
        window.display();

    }

    return 0;
}
