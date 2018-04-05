#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Timer.h"


using namespace std;
using namespace sf;


// on v�rifie que le sprite contient la souris
bool sprite_mouse(RenderWindow* window, Vector2i position_mouse, Sprite sprite){
    position_mouse = Mouse::getPosition(*window);
    //cout << "Mouse.x :" << position_souris.x << "Mouse.y :" << position_souris.y << endl;
    return sprite.getGlobalBounds().contains(position_mouse.x,position_mouse.y);
}

vector<vector<string>> card_import(){
    string line;
    char letter;
    int lengh=80;
    ifstream file ("card_export.csv",ios::in);
    vector <vector<string> > card(lengh);
    int index=0;
    int id=0;

    for(int i = 0; i<lengh;i++){

        card[i]=vector<string>(10);
    }

      // Si mon fichier est ouvert
      if (file.is_open()){
      // Tant qu'on a pas parcouru tout le fichier
        while ( getline (file,line) ){

          cout << line << endl;
          lengh=line.size();
          id=0;
          for(int i=0; i<lengh; i++){
                letter=line[i];
                if(letter==';'){
                    id++;
                }else{
                    card[index][id]=card[index][id]+letter;
                }
          }

          for(int i=0; i<10; i++){
                cout << card[index][i] << " ";
          }
          cout<<endl;
          index++;
        }
        // Fermer le fichier

        file.close();
      }

      else {

            cerr << "Impossible d'ouvrir le fichier" << endl;
      }
      return card;
}

// fonction pour g�rer le menu
void menu(RenderWindow* window, Vector2i position_mouse,Sprite play,Sprite leave, int* interface){
    // si le bouton jouer contient la souris
    if(sprite_mouse(window,position_mouse,play)){
            // on change sa couleur
            play.setColor(Color(100,250,100));
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
            leave.setColor(Color(100,250,100));
            // si on clique la fen�tre se ferme
            if(Mouse::isButtonPressed(Mouse::Left)){
                window->close();
            }
        }else{
            // sinon le bouton reprend sa couleur
            leave.setColor(Color(255,255,255));
        }
        // on dessine le bouton jouer et quitter sur la fen�tre
        window->draw(play);
        window->draw(leave);
}

// fonction contenant le futur code du jeu
void game(){


}

int main()
{
    Vector2f windowsize;
    windowsize.x=1600;
    windowsize.y=900;
    // fen�tre principale avec sa taille et son nom
    RenderWindow window(VideoMode(windowsize.x,windowsize.y), "LES TOURS");
    // Vector2i est l'�quivalent d'un point il peut contenir deux valeurs, plus tard on lui affectera les coordonn�es de la souris
    Vector2i position_mouse;
    // sprite des boutons du menu
    Sprite play, leave;
    // variable d�finissant si on est sur le menu ou dans une partie
    int interface = 1;
    // limite les fps pour ne pas faire surchauffer la carte graphique
    window.setFramerateLimit(60);
    // cr�ation de l'objet plateau et des cases
    Board board;
    board.liaison();
    vector<vector<string>>card=card_import();

    Timer chrono(windowsize);

    // on d�finit des textures et on leur donne une image
    Texture texture_play, texture_leave;

    if (!texture_play.loadFromFile("image/button_jouer.png")){
        cout << "erreur";
    }
    if (!texture_leave.loadFromFile("image/button_quit.png")){
        cout << "erreur";
    }
    //on donne cette texture aux sprites, et on leur donne des coordonn�es
    play.setTexture(texture_play);
    play.setPosition(windowsize.x/3, windowsize.y/3);
    leave.setTexture(texture_leave);
    leave.setPosition(windowsize.x/3, windowsize.y/2);


    // Affichage tu titre du jeu
    Font title;
    if(!title.loadFromFile("font/dumbledor.ttf")){
        cerr<<"Fichier font 'dumbledor.ttf' introuvable"<<endl;
    }
    Text titleGame;
    titleGame.setString("Battle Tower");
    titleGame.setFont(title);
    titleGame.setCharacterSize(100);
    titleGame.setPosition(3*windowsize.x/9, windowsize.y/16);
    titleGame.setFillColor(sf::Color::White);

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
            menu(&window,position_mouse,play,leave,&interface);
            window.draw(titleGame);
        }else{
             // execution du jeu
            game();
            board.display(&window);
            board.collision(&window);
            chrono.echo(&window);

            // condition inutile c'�tait juste pour mes tests
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
