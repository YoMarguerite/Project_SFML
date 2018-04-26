#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Menu.h"

using namespace std;
using namespace sf;

bool sprite_mouse(RenderWindow* window, Vector2i position_mouse, Sprite sprite){
    position_mouse = Mouse::getPosition(*window);
    //cout << "Mouse.x :" << position_souris.x << "Mouse.y :" << position_souris.y << endl;
    return sprite.getGlobalBounds().contains(position_mouse.x,position_mouse.y);
}

Menu::Menu(Vector2f windowsize){

    bckg.setTexture(textureBkg);
    bckg.setPosition(0,0);
    // ____________________ BOUTONS _____________________________

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

    // Affichage tu titre du jeu
    Font title;
    if(!title.loadFromFile("font/dumbledor.ttf")){
        cerr<<"Fichier font 'dumbledor.ttf' introuvable"<<endl;
    }

    Text titleGame;
    titleGame.setString("Battle Tower");
    titleGame.setFont(title);
    titleGame.setCharacterSize(100);
    titleGame.setPosition(3*windowsize.x/9, windowsize.y/9);
    titleGame.setFillColor(sf::Color::White);


}

// Méthode concernant le menu
void Menu::display(RenderWindow* window, Vector2i position_mouse, int* interface){
    // si le bouton jouer contient la souris
    if(sprite_mouse(window,position_mouse,play)){
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
    if(sprite_mouse(window,position_mouse,leave)){
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
    // on dessine le bouton jouer et quitter sur la fenêtre
    window->draw(bckg);
    window->draw(titleGame);
    window->draw(play);
    window->draw(leave);
}
