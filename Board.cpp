#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"

using namespace std;
using namespace sf;

CircleShape hex(int posx, int posy){

    // taille d'un côté et nombre de points
    CircleShape hexagon(50, 6);
    // couleur et épaisseur de la bordure extérieur
    hexagon.setOutlineColor(Color(250,150,100));
    hexagon.setOutlineThickness(3);
    // positionnement de l'hexagone
    hexagon.setRotation(90);
    hexagon.setPosition(posx,posy);

    return hexagon;
}

Board::Board(Player* joueur){
    joueur1=joueur;
// création de chaque case puis on conserve leurs adresses dans le vecteur tab
    for(int i=0; i<50 ; i++){
        tab.push_back(new Square(i));
    }

// création de chaque hexagone avec leurs positions
    int lengh=graphics_board.size();
    int i=1;
    int posx=555, posy=40, decy=188;

    while(lengh<50){

        if((lengh==3) || (lengh==9) || (lengh==16) || (lengh==22) || (lengh==25)
           || (lengh==28) || (lengh==34) || (lengh==41) || (lengh==47)){
            i=1;
        }
        if((lengh == 3) || (lengh == 9) || (lengh == 16) || (lengh == 22)
           || (lengh == 28) || (lengh == 34) || (lengh == 41) || (lengh == 47)){
            posx+=82;
        }
        if((lengh==9) || (lengh==22) || (lengh==34)){
            posy=40;
        }
        if((lengh==3) || (lengh==16) || (lengh==28) ||(lengh==41)){
            posy=88;
        }
        if(lengh==25){
            posy=417;
        }
        if(lengh == 3){
            decy=94;
        }
        if(lengh == 47){
            posy=40;
            decy=188;
        }
        tab[lengh]->setpos(posx,i*decy+posy);
        graphics_board.push_back(hex(posx,i*decy+posy));
        lengh=graphics_board.size();
        i++;
    }
}

// destructeur du plateau et de chaque case
Board::~Board(){
    int taille = tab.size();
    for(int i = 0; i<taille-1; i++){
        delete tab[i];
    }
}

//affichage du contenu de tab
void Board::echo(){

    int taille = tab.size();
    cout << "Vector[" << taille << "] : ";
    for(int i = 0 ; i < taille; i++){
        cout << tab[i] << " ";
    }
    cout << endl;
}

// affichage d'une case précise identifiée par son id
void Board::echo_case(int id){

    cout << "Case N°" << id << endl;
    cout << "Type : " << tab[id]->gettype() << endl;
    cout << "Camp : " << tab[id]->getcamp() << endl;
    cout << "Cases proches : " << endl;
    int longueur = tab[id]->getnearby().size();
    for(int i=0; i<longueur ; i++){
        cout << "id : " << tab[id]->getnearby()[i]->getnumero() << " , " << tab[id]->getnearby()[i] << endl;
    }

}

// retourne les valeurs de tab donc les adresses de chaque case
vector<Square*>& Board::get() {

  return tab;

}

// définie les liaisons de chaque case avec les cases adjacentes
void Board::liaison(){
    int lengh = tab.size();
    for(int i = 0; i < lengh; i++){

            if(((i > 9) && (i < 25) && (i != 22)) || ((i > 31) && (i < 47) && (i != 34))){

                tab[i]->setnearby(tab[i-7]);
            }
            if((i > 7) && (i < 48) && (i != 15) && (i != 40)){

                tab[i]->setnearby(tab[i-6]);
            }
            if((i == 6) || (i == 7) || ((i > 24) && (i < 30) && (i != 27)) || (i == 47) || (i == 48)){

                tab[i]->setnearby(tab[i-5]);
            }
            if((i == 4) || (i == 5) || (i == 48) || (i == 49)){

                tab[i]->setnearby(tab[i-4]);
            }
            if((i == 3) || (i == 49)){

                tab[i]->setnearby(tab[i-3]);
            }
            if((i > 3) && (i !=9) && (i != 16) && (i != 22) && (i != 25) && (i != 28) && (i != 34) && (i != 41) && (i < 47)){

                tab[i]->setnearby(tab[i-1]);
            }
            if((i > 2) && (i !=8) && (i != 15) && (i != 21) && (i != 24) && (i != 27) && (i != 33) && (i != 40) && (i < 46)){

                tab[i]->setnearby(tab[i+1]);
            }
            if((i == 0) || (i == 46)){

                tab[i]->setnearby(tab[i+3]);
            }
            if((i == 0) || (i == 1) || (i == 44) || (i == 45)){

                tab[i]->setnearby(tab[i+4]);
            }
            if((i == 1) || (i == 2) || ((i > 19) && (i < 25) && (i != 22)) || (i == 42) || (i == 43)){

                tab[i]->setnearby(tab[i+5]);
            }
            if((i > 1) && (i < 42) && (i != 9) && (i != 34)){

                tab[i]->setnearby(tab[i+6]);
            }
            if(((i > 2) && (i < 18) && (i != 15)) || ((i > 24) && (i < 40) && (i != 27))){

                tab[i]->setnearby(tab[i+7]);
            }
    }
}

// affichage sur l'écran des hexagones des cases
void Board::display(RenderWindow* window){

    for(int i = 0; i<50; i++){

            window->draw(graphics_board[i]);
    }
    for(unsigned int i=0;i<allcard.size();i++){
        window->draw(allcard[i]->getimage());
    }
}

// gestion de la collision de chaque case avec la souris
void Board::collision(RenderWindow* window){
    // on fait défiler tous les hexagones
    for(int i=0; i<50; i++){
        // on récupère les coordonnées de la souris
        Vector2i position_mouse = Mouse::getPosition(*window);
        // on vérifie que l'hexagone contient la souris
        if(graphics_board[i].getGlobalBounds().contains(position_mouse.x,position_mouse.y)){
            // si c'est le cas on change sa couleur en magenta
            graphics_board[i].setFillColor(Color(186, 186, 186));
            // si on clique les caractéristiques de la case s'affiche
            if(Mouse::isButtonPressed(Mouse::Left)){
                while(Mouse::isButtonPressed(Mouse::Left)){}
                echo_case(i);
//                if(tab[i]->getcamp()=="Joueur 1"){
                    int select=joueur1->getselect();
                    if(select!=-1){
                        tab[i]->setpawn(joueur1->getcard(select), tab[i]->getpos());
                        Vector2f j=tab[i]->getpos();
                        cout<<j.x<<endl;
                        cout<<j.y<<endl;
                        joueur1->addCardPlaced(tab[i]->getpawn(),select);
                        setallcard(tab[i]->getpawn());
                    }
//                }
            }
        }else{
            // si l'hexagone ne contient pas la souris on lui redonne sa couleur d'origine
            graphics_board[i].setFillColor(Color(tab[i]->getred(),tab[i]->getgreen(),tab[i]->getblue()));
        }
    }
}

void Board::setallcard(CardBoard* card){
    allcard.push_back(card);
}
