#include <iostream>
#include <SFML/Graphics.hpp>
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


// on vérifie que le sprite contient la souris



// fonction pour gérer le menu



// fonction contenant le futur code du jeu
void game(RenderWindow* window, Vector2i position_mouse, Sprite exit, int* interface){
    // si le bouton quitter contient la souris
    if(sprite_mouse(window,position_mouse,exit)){
        // on change sa couleur
        exit.setColor(Color(150,150,150));
        // si on clique la fenêtre se ferme
        if(Mouse::isButtonPressed(Mouse::Left)){
             *interface=1;
        }
    }else{
        // sinon le bouton reprend sa couleur
        exit.setColor(Color(255,255,255));

    }
    // on dessine le bouton jouer et quitter sur la fenêtre
    window->draw(exit);
 }

int main()
{
    // Taille de la fenêtre
    Vector2f windowsize;
    windowsize.x=1600;
    windowsize.y=1000;

    // fenêtre principale avec sa taille et son nom
    RenderWindow window(VideoMode(windowsize.x,windowsize.y), "LES TOURS");
    // Vector2i est l'équivalent d'un point il peut contenir deux valeurs, plus tard on lui affectera les coordonnées de la souris
    Vector2i position_mouse;

    Console console;

    Menu menu(windowsize);

    // variable définissant si on est sur le menu ou dans une partie
    int interface = 1;
    // limite les fps pour ne pas faire surchauffer la carte graphique
    window.setFramerateLimit(60);
    // création de l'objet plateau et des cases
    Statcard stat;

    Player joueur1(&stat);
    Player joueur2(&stat);

    Board board(&joueur1);
    board.liaison();

    // Chronomètre
    Timer chrono(windowsize,&joueur1,&joueur2);

    //    Chargement de la texture pour le background du Menu


    //    Chargement de la texture pour le background du Jeu
    Texture textureBkg2;
    if (!textureBkg2.loadFromFile("image/backgroundGame.jpg")){
        cout << "erreur";
    }

    //    Chargement de la texture pour le background
    Sprite bckg2;

    //on donne cette texture aux sprites, et on leur donne des coordonnées
    bckg2.setTexture(textureBkg2);
    bckg2.setPosition(0,0);

    // on définit des textures et on leur donne une image

    //on donne cette texture aux sprites, et on leur donne des coordonnées



    // --------------------------- TITRE DU JEU ------------------------------


    // Affichage tu titre du jeu


    // ------------------- QUITTER LE JEU EN COURS DE PARTIE -------------------

    Sprite exit;
    Texture exitGame;
	if (!exitGame.loadFromFile("image/button_exit.png")) {
		cout << "erreur";
	}
 	exit.setTexture(exitGame);
 	exit.setPosition((windowsize.x)-(windowsize.x)/17,windowsize.x/90);

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
        // on vérifie sur qu'elle interface on est menu ou en jeu
        if(interface == 1){
            // execution du menu


        }else{
            window.draw(bckg2);
             // execution du jeu
            game(&window, position_mouse,exit,&interface);
            board.display(&window);
            board.collision(&window);
            chrono.echo(&window);
            chrono.endturn(&window);
            joueur1.displayHand();
            joueur1.echoHand(&window);
            joueur1.stockMana(&window);

            // condition inutile c'était juste pour mes tests
            if(Keyboard::isKeyPressed(Keyboard::A)){
                int id = -1;
                while(( id < 0 ) || (id > 49)){
                    cin >> id;
                }
                board.echo_case(id);
            }
        }

        window.display();

    }

    return 0;
}
