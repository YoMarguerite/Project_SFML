#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include "Plateau.h"


using namespace std;
using namespace sf;

// déclaration en dehors du main pour pouvoir les utiliser dans tout le programme
// sprite des boutons du menu
Sprite play, leave;
// fenêtre principale avec sa taille et son nom
RenderWindow window(VideoMode(1200,800), "LES TOURS");
// Vector2i est l'équivalent d'un point il peut contenir deux valeurs, plus tard on lui affectera les coordonnées de la souris

// variable définissant si on est sur le menu ou dans une partie
int interface = 1;





// on vérifie que le sprite contient la souris
bool sprite_mouse(Vector2i position_mouse, Sprite sprite){
    position_mouse = Mouse::getPosition(window);
    //cout << "Mouse.x :" << position_souris.x << "Mouse.y :" << position_souris.y << endl;
    return sprite.getGlobalBounds().contains(position_mouse.x,position_mouse.y);
}

vector<vector<string>> card_import(){
    string ligne;
    char colonne;
    int taille=80;
    vector<string>c;
    ifstream fichier ("card_export.csv",ios::in);
    vector <vector<string> > card(taille);
    int indice=0;
    int id=0;

    for(int i = 0; i<taille;i++){

        card[i]=vector<string>(10);
    }

      // Si mon fichier est ouvert
      if (fichier.is_open()){
      // Tant qu'on a pas parcouru tout le fichier
        while ( getline (fichier,ligne) ){

          cout << ligne << endl;
          taille=ligne.size();
          id=0;
          for(int i=0; i<taille; i++){
                colonne=ligne[i];
                if(colonne==';'){
                    id++;
                }else{
                    card[indice][id]=card[indice][id]+colonne;
                }
          }

          for(int i=0; i<10; i++){
                cout << card[indice][i] << " ";
          }
          cout<<endl;
          indice++;
        }
        // Fermer le fichier

        fichier.close();
      }

      else {

            cerr << "Impossible d'ouvrir le fichier" << endl;
      }
      return card;
}

// fonction pour gérer le menu
void menu(Vector2i position_mouse){
    // si le bouton jouer contient la souris
    if(sprite_mouse(position_mouse,play)){
            // on change sa couleur
            play.setColor(Color(100,250,100));
            // si on clique
            if(Mouse::isButtonPressed(Mouse::Left)){
                // le jeu commence et on change d'interface
                cout << "Le jeu commence" << endl;
                interface = 2;
            }
        }else{
            // sinon on lui redonne sa couleur d'origine
            play.setColor(Color(255,255,255));
        }

        // si le bouton quitter contient la souris
        if(sprite_mouse(position_mouse,leave)){
            // on change sa couleur
            leave.setColor(Color(100,250,100));
            // si on clique la fenêtre se ferme
            if(Mouse::isButtonPressed(Mouse::Left)){
                window.close();
            }
        }else{
            // sinon le bouton reprend sa couleur
            leave.setColor(Color(255,255,255));
        }
        // on dessine le bouton jouer et quitter sur la fenêtre
        window.draw(play);
        window.draw(leave);
}

// fonction contenant le futur code du jeu
void jeu(){


}

int main()
{
    Vector2i position_mouse;
    // limite les fps pour ne pas faire surchauffer la carte graphique
    window.setFramerateLimit(60);
    // création de l'objet plateau et des cases
    Plateau plateau;
    plateau.liaison();
    vector<vector<string>>card=card_import();

    // on définit des textures et on leur donne une image
    Texture texture_play, texture_leave;

    if (!texture_play.loadFromFile("image/button_jouer.png")){
        cout << "erreur";
    }
    if (!texture_leave.loadFromFile("image/button_quit.png")){
        cout << "erreur";
    }
    //on donne cette texture aux sprites, et on leur donne des coordonnées
    play.setTexture(texture_play);
    play.setPosition(Vector2f(400, 400));
    leave.setTexture(texture_leave);
    leave.setPosition(Vector2f(400,600));

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
            menu(position_mouse);
        }
        if(interface == 2){

            // execution du jeu
            jeu();
            plateau.afficher(&window);
            plateau.collision(&window);

            // condition inutile c'était juste pour mes tests
            if(Keyboard::isKeyPressed(Keyboard::A)){
                int id = -1;
                while(( id < 0 ) || (id > 49)){
                    cin >> id;
                }
                plateau.echo_case(id);
            }

        }

        window.display();

    }

    return 0;
}


