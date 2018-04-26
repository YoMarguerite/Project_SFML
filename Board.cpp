#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Board.h"
#include "Player.h"

using namespace std;
using namespace sf;

//créateur des cases de manière graphique
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
//constructeur du plateau
Board::Board(Player* joueur){
    joueur1=joueur;
// création de chaque case puis on conserve leurs adresses dans le vecteur tab
    for(int i=0; i<50 ; i++){
        tab.push_back(new Square(i));
    }

// création de chaque hexagone avec leurs positions, hexagone=case graphique
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
        //sauvegarde des coordonnées dans la class
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
            // si c'est le cas on change sa couleur
            graphics_board[i].setFillColor(Color(186, 186, 186));
            // si on clique
            if(Mouse::isButtonPressed(Mouse::Left)){
                //on bloque la souris, l'action se fera quand l'utilisateur ne cliquera plus
                while(Mouse::isButtonPressed(Mouse::Left)){}
                //les caractéristiques de la case s'affiche
                    echo_case(i);
                    //on récupère la carte sélectionné par le joueur
                    int select=joueur1->getselect();
                    //si une carte est sélectionnée, que la case appartient au joueur1 que ce n'est pas une tour et qu'elle est vide
                    if((select!=-1)&&(tab[i]->getcamp()=="Joueur 1")&&(tab[i]->gettype()!="Tour")&&(tab[i]->getempty()==true)){
                            //si le joueur a assez de mana pour poser la carte
                        if(joueur1->checkmana(select) && joueur1->getActive()== true){
                            //le mana est dépensé
                            joueur1->spendmana(select);
                            //on pose la carte sur la case
                            tab[i]->setpawn(joueur1->getcard(select), tab[i]->getpos());
                            //le joueur 1 déplace la carte de la main jusqu'à ses cartes de plateau
                            joueur1->addCardPlaced(tab[i]->getpawn(),select);
                            //la carte est aussi sauvegardée dans la class plateau
                            setallcard(tab[i]->getpawn());
                            //on désélectionnes la carte
                            joueur1->deselect();
                        }
                    }
                    //si la case est occupée
                    if(tab[i]->getempty()==false){
                        //on récupère les points de déplacements de l'unité
                        tab[i]->getpawn()->getmovement();
                        //on récupère les cases proches
                        vector<Square*>SquareSelect=tab[i]->getnearby();
                        //on les sélectionnes
                        for(unsigned int i=0;i<SquareSelect.size();i++){
                            SquareSelect[i]->setselect();
                        }

                    }
            }
        }else{
            //si une case est sélectionnée sa couleur change
            if(tab[i]->getselect()){
                graphics_board[i].setFillColor(Color(50,200,150));
            }else{
                // sinon si l'hexagone ne contient pas la souris on lui redonne sa couleur d'origine
                graphics_board[i].setFillColor(Color(tab[i]->getred(),tab[i]->getgreen(),tab[i]->getblue()));
            }
        }
    }
}
//on ajoute une carte sur le plateau
void Board::setallcard(CardBoard* card){
    allcard.push_back(card);
}
//on déselectionnes toutes les cases
void Board::deselect(){
    if(Mouse::isButtonPressed(Mouse::Right)){
        for(int i=0; i<50; i++){
            tab[i]->deselect();
        }
    }
}
