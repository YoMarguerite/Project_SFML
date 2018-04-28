#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace std;
using namespace sf;


//constructeur du menu
Menu::Menu(Vector2f windowsize){
    //importation de l'image du background
    if (!textureBkg.loadFromFile("image/backgroundMenu.png")){
        cout << "erreur";
    }

    bckg.setTexture(textureBkg);
    bckg.setPosition(0,0);
    // ____________________ BOUTONS _____________________________

    //importation des images des boutons
    if (!texture_play.loadFromFile("image/button_jouer.png")){
        cout << "erreur";
    }

    if (!texture_leave.loadFromFile("image/button_quit.png")){
        cout << "erreur";
    }

    //on donne cette texture aux sprites, et on leur donne des coordonnées
    play.setTexture(texture_play);
    play.setPosition(windowsize.x/3, 4*windowsize.y/9);
    leave.setTexture(texture_leave);
    leave.setPosition(windowsize.x/3, 5.5*windowsize.y/9);

    // mise en place tu titre du jeu

    if(!title.loadFromFile("font/dumbledor.ttf")){
        cerr<<"Fichier font 'dumbledor.ttf' introuvable"<<endl;
    }

    titleGame.setString("Battle Tower");
    titleGame.setFont(title);
    titleGame.setCharacterSize(100);
    titleGame.setPosition(3*windowsize.x/9, windowsize.y/9);
    titleGame.setFillColor(sf::Color::White);

}



// Méthode concernant le menu, affichage

void Menu::display(RenderWindow* window, int* interface){

    //on récupère les coordonnées de la souris

    Vector2i position_mouse=Mouse::getPosition(*window);

    // si le bouton jouer contient la souris

    if(play.getGlobalBounds().contains(position_mouse.x,position_mouse.y)){

            // on change sa couleur
            play.setColor(Color(57,206,107));
            // si on clique
            if(Mouse::isButtonPressed(Mouse::Left)){
                // le jeu commence et on change d'interface
                cout << "Le jeu commence" << endl;
                *interface = 2;
            }
        }else{
            // sinon on lui redonne sa couleur d'origine
            play.setColor(Color(255,255,255));
        }

    // si le bouton quitter contient la souris
    if(leave.getGlobalBounds().contains(position_mouse.x,position_mouse.y)){
        // on change sa couleur
        leave.setColor(Color(150,150,150));
        // si on clique la fenêtre se ferme
        if(Mouse::isButtonPressed(Mouse::Left)){
            window->close();
        }
    }else{
        // sinon le bouton reprend sa couleur
        leave.setColor(Color(255,255,255));
    }

    // on affiche le background, le titre, le bouton jouer et quitter sur la fenêtre

    window->draw(bckg);
    window->draw(titleGame);
    window->draw(play);
    window->draw(leave);
}
