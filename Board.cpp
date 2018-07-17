#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Board.h"


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
Board::Board(Player* joueur1,Player* joueur2){
    this->joueur=joueur1;
    joueurs.push_back(joueur1);
    joueurs.push_back(joueur2);
    PlaySquare=-1;
    victory = false;
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
    if(!image.loadFromFile("image/parchemin.png")){
        cout<<"image parchemin.png introuvable"<<endl;
    }
    parchemin.setTexture(image);
    parchemin.setScale(0.7,0.7);
    parchemin.setPosition(1250,200);
    if(!font.loadFromFile("font/dumbledor.ttf")){
        cout<<"font introuvable"<<endl;
    }
    stats=vector<Text>(5);
    for(unsigned int i=0;i<stats.size();i++){
        stats[i].setFont(font);
        stats[i].setPosition(1350,240+i*50);
        stats[i].setFillColor(Color::Black);
    }
}

// destructeur du plateau et de chaque case
Board::~Board(){

    for(unsigned int i = 0; i < tab.size(); i++){
        delete tab[i];
    }
    tab.clear();
    SquareSelect.clear();

    for(unsigned int i = 0; i < allcard.size(); i++){
        delete allcard[i];
    }
    allcard.clear();
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
vector<Square*> Board::get() {
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

vector<CardBoard*> Board::settower(Card* tower){

    vector<CardBoard*> towers;

    for(unsigned int i=0;i<tab.size();i++){
        if(tab[i]->gettype()=="Tour"){
            tab[i]->setpawn(tower,tab[i]->getpos(),tab[i]->getcamp());
            tab[i]->getpawn()->setplace(setallcard(tab[i]->getpawn())-1);
            towers.push_back(tab[i]->getpawn());
        }
    }
    return towers;
}

// affichage sur l'écran des hexagones des cases
void Board::display(RenderWindow* window){

    for(int i = 0; i<50; i++){
            window->draw(graphics_board[i]);
    }
    for(unsigned int i=0;i<allcard.size();i++){
        if(allcard[i]->getanim()>0){
            Vector2f position=allcard[i]->getimage().getPosition();
            position.x+=100;
            Vector2f ecart=(allcard[i]->getposition()-position);
            ecart.x=ecart.x/allcard[i]->getanim();
            ecart.y=ecart.y/allcard[i]->getanim();
            position.x+=ecart.x;
            position.y+=ecart.y;
            allcard[i]->duringanim();
            allcard[i]->setimageposition(position);
        }
        window->draw(allcard[i]->getimage());
        window->draw(allcard[i]->getvie());
        window->draw(allcard[i]->getattaque());
        window->draw(allcard[i]->getmoving());
    }
    if(PlaySquare!=-1){

        window->draw(parchemin);

        stats[0].setString(tab[PlaySquare]->getpawn()->getname());
        stats[1].setString(tab[PlaySquare]->getpawn()->getcamp());

        int int_to_string=tab[PlaySquare]->getpawn()->getdamage();
        char* string_fin;
        sprintf(string_fin, "%d", int_to_string);

        string setstring="ATQ : ";
        setstring+=string_fin;
        stats[2].setString(setstring);
        int_to_string=tab[PlaySquare]->getpawn()->getlife();
        sprintf(string_fin, "%d", int_to_string);

        setstring="PV     : ";
        setstring+=string_fin;
        stats[3].setString(setstring);
        int_to_string=tab[PlaySquare]->getpawn()->getbuild();
        sprintf(string_fin, "%d", int_to_string);

        setstring="PM    : ";
        setstring+=string_fin;
        stats[4].setString(setstring);

        for(unsigned int i=0; i<stats.size();i++){

            window->draw(stats[i]);
        }
    }
}

void Board::selectsquare(int i){

    deselect();

    PlaySquare=i;

    if(tab[PlaySquare]->getpawn()->getbuild() == -1){

        SquareSelect=tab[PlaySquare]->getnearby();

        for(unsigned int i=0;i<SquareSelect.size();i++){
            if(SquareSelect[i]->getempty()){

                if(tab[PlaySquare]->getpawn()->getmovement()>0){
                    SquareSelect[i]->setselect();
                }
            }else if((tab[PlaySquare]->getpawn()->getcoup()>0)&&(SquareSelect[i]->getpawn()->getcamp()!=joueur->getname())){
                SquareSelect[i]->setselect();
            }
        }
    }
}

void Board::movementpawn(int i){
    tab[i]->movepawn(tab[PlaySquare]->getpawn());
    tab[i]->getpawn()->setmovement();
    tab[i]->getpawn()->setposition(tab[i]->getpos());
    tab[i]->getpawn()->setanim();
    tab[PlaySquare]->setempty();
    selectsquare(i);
}

// gestion de la collision de chaque case avec la souris
void Board::collision(RenderWindow* window){
    bool hover=false;
    // on fait défiler tous les hexagones
    for(int i=0; i<50; i++){

        Vector2i position_mouse = Mouse::getPosition(*window);
        // on vérifie que l'hexagone contient la souris
        if((graphics_board[i].getGlobalBounds().contains(position_mouse.x,position_mouse.y))&&(!hover)){
            hover=true;

            graphics_board[i].setFillColor(Color(186, 186, 186));

            if(Mouse::isButtonPressed(Mouse::Left)){
                //on bloque la souris, l'action se fera quand l'utilisateur ne cliquera plus
                while(Mouse::isButtonPressed(Mouse::Left)){}
                    //on récupère la carte sélectionné par le joueur
                    int select=joueur->getselect();

                    if((select!=-1)&&(tab[i]->getcamp()==joueur->getname())&&(tab[i]->gettype()!="Tour")&&(tab[i]->getempty())){

                        if((joueur->checkmana(select)) && (joueur->getActive())){

                            joueur->spendmana(select);

                            tab[i]->setpawn(joueur->getcard(select), tab[i]->getpos(), joueur->getname());

                            joueur->addCardPlaced(tab[i]->getpawn(),select);

                            tab[i]->getpawn()->setplace(setallcard(tab[i]->getpawn())-1);

                            joueur->deselect();

                            selectsquare(i);
                        }
                    }

                    if(!tab[i]->getempty()){
                        if((tab[i]->getpawn()->getcamp()==joueur->getname())){
                            selectsquare(i);
                        }
                        if((tab[i]->getpawn()->getcamp()!=joueur->getname())&&(!tab[i]->getselect())){
                            deselect();
                            PlaySquare=i;
                        }
                    }
                    if(tab[i]->getselect()){
                        if(tab[i]->getempty()){
                            movementpawn(i);
                        }else if((tab[i]->getpawn()->getcamp()!=joueur->getname())&&(tab[PlaySquare]->getpawn()->getcoup()>0)){
                            if(tab[i]->getpawn()->takedamage(tab[PlaySquare]->getpawn())){
                                tab[i]->setempty();

                                if(tab[i]->getpawn()->getcamp() == "Joueur 1"){

                                    if(joueurs[0]->destruct(allcard[tab[i]->getpawn()->getplace()])){
                                        cout<<"victoire : joueur 2"<<endl;
                                        victory = true;
                                    }
                                }else{


                                    if(joueurs[1]->destruct(allcard[tab[i]->getpawn()->getplace()])){
                                        cout<<"victoire : joueur 1"<<endl;
                                        victory = true;
                                    }
                                }

                                allcard.erase(allcard.begin()+tab[i]->getpawn()->getplace());

                                for(unsigned int j=0;j<allcard.size();j++){
                                    allcard[j]->setplace(j);
                                }
                                selectsquare(PlaySquare);
                            }
                        }
                    }
            }
        }else{

            graphics_board[i].setFillColor(Color(tab[i]->getred(),tab[i]->getgreen(),tab[i]->getblue()));

            if(tab[i]->getselect()){
                if(tab[i]->getempty()){
                    graphics_board[i].setFillColor(Color(50,200,150));
                }else{
                    graphics_board[i].setFillColor(Color(240,120,120));
                }
            }
        }
    }
}

int Board::setallcard(CardBoard* card){
    allcard.push_back(card);
    return allcard.size();
}


void Board::deselect(){
    for(int i=0; i<50; i++){
        tab[i]->deselect();
    }
    PlaySquare=-1;
}


void Board::setplayer(Player* joueur){
    this->joueur=joueur;
}


bool Board::getvictory(){
    return victory;
}
