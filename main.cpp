#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "class.h"


using namespace std;
using namespace sf;

Sprite jouer, quitter;
RenderWindow window(VideoMode(1200,800), "6 battle keep");
Vector2i position_souris;
int interface = 1;


class Emplacement{

public:
    int numero;
    int rouge;
    int vert;
    int bleu;
    bool vide;
    bool mana;
    bool poison;
    string camp;
    string type;
    vector<Emplacement*> proche;

    Emplacement(int id);
    vector<Emplacement*>& get();

};

Emplacement::Emplacement(int id){

    numero = id;

    if(id < 16){
        camp = "Joueur 1";
        if(id < 3){
            type = "Tour";
            rouge=255;
            vert=100;
            bleu=0;
        }else{
            type = "Case";
            rouge=20;
            vert=255;
            bleu=30;
        }
    }else if(id < 32){
        camp = "Joueur 2";
        if(id < 19){
            type = "Tour";
            rouge=255;
            vert=100;
            bleu=0;
        }else{
            type = "Case";
            rouge=20;
            vert=255;
            bleu=30;
        }
    }else{
        camp = "Neutre";
        if((id  == 38) || (id == 43)){
            type = "Puit de mana";
            rouge=100;
            vert=185;
            bleu=255;
        }else{
            type = "Case";
            rouge=240;
            vert=240;
            bleu=240;
        }
    }
}

vector<Emplacement*>& Emplacement::get(){

    return proche;
}



class Plateau{

private:
    vector<Emplacement*> tab;
    vector<CircleShape> plateau_graphique;

public:
    Plateau();
    ~Plateau();
    void echo();
    void echo_case(int id);
    void liaison();
    vector<Emplacement*>& get();
    void afficher();
    void collision();

};


Plateau::Plateau(){

    for(int i=0; i<50 ; i++){
        Emplacement* pointeur;
        pointeur = new Emplacement(i);
        tab.push_back(pointeur);
    }

    int taille=plateau_graphique.size();
    int i=1;
    int posx=400, posy=40, decy=136;
    int rouge=255, vert=100, bleu=0;

    while(taille<50){

        if((taille==3) || (taille==9) || (taille==16) || (taille==19) || (taille==25)
           || (taille==32) || (taille==38) || (taille==41) || (taille==44)){

            i=1;
        }
        if((taille==9) || (taille==25) || (taille==38)){
            posy=40;
        }
        if((taille==3) || (taille==19) || (taille==32) ||(taille==44)){
            posy=74;
        }
        if((taille==3) || (taille==19)){
            rouge=20;
            vert=255;
            bleu=30;
        }

        if((taille == 3) || (taille == 9) || (taille == 38) || (taille == 44)){
            posx+=60;
        }

        if((taille == 19) || (taille == 25)){
            posx-=60;
        }


        if((taille == 3) || (taille == 19)){
            decy=68;
        }

        if(taille==16){
            posx+=360;
            decy=136;
            rouge=255;
            vert=100;
            bleu=0;
        }
        if(taille>31){
            rouge=240;
            vert=240;
            bleu=240;
        }
        if(taille==32){
            posx-=180;
        }
        if(taille==41){
            posy=312;
        }
        if((taille==38) || (taille==43)){
            rouge=100;
            vert=185;
            bleu=255;
        }


        plateau_graphique.push_back(hex(posx,i*decy+posy,rouge,vert,bleu));
        taille=plateau_graphique.size();
        i++;
    }
}


Plateau::~Plateau(){
    int taille = tab.size();
    for(int i = 0; i<taille-1; i++){
        delete tab[i];
    }
}


void Plateau::echo(){

    int taille = tab.size();
    cout << "Vector[" << taille << "] : ";
    for(int i = 0 ; i < taille; i++){
        cout << tab[i] << " ";
    }
    cout << endl;
}

void Plateau::echo_case(int id){

    cout << "Case N°" << id << endl;
    cout << "Type : " << tab[id]->type << endl;
    cout << "Camp : " << tab[id]->camp << endl;
    cout << "Cases proches : " << endl;
    int longueur = tab[id]->proche.size();
    for(int i=0; i<longueur ; i++){
        cout << "id : " << tab[id]->proche[i]->numero << " , " << tab[id]->proche[i] << endl;
    }

}


vector<Emplacement*>& Plateau::get() {

  return tab;

}


void Plateau::liaison(){
    int taille = tab.size();
    for(int i = 0; i < taille; i++){

        if((i == 0) || (i == 16)){

            tab[i]->proche.push_back(tab[i+3]);
            tab[i]->proche.push_back(tab[i+4]);
        }
        if((i == 1) || (i == 17)){

            tab[i]->proche.push_back(tab[i+4]);
            tab[i]->proche.push_back(tab[i+5]);
        }
        if((i == 2) || (i == 18)){

            tab[i]->proche.push_back(tab[i+5]);
            tab[i]->proche.push_back(tab[i+6]);
        }
        if(((i > 2) && (i < 8)) || ((i > 8) && (i < 15)) || ((i > 18) && (i < 24)) || ((i > 24) && (i < 31))
            || ((i > 31) && (i < 37)) || ((i > 37) && (i < 40)) || ((i > 40) && (i < 43)) || ((i > 43) && (i < 49))) {

            tab[i]->proche.push_back(tab[i+1]);
        }
        if(((i > 3) && (i < 9)) || ((i > 9) && (i < 16)) || ((i > 19) && (i < 25)) || ((i > 25) && (i < 32))
            || ((i > 32) && (i < 38)) || ((i > 38) && (i < 41)) || ((i > 41) && (i < 44)) || (i > 44)) {

            tab[i]->proche.push_back(tab[i-1]);
        }
        if(((i > 2) && (i < 9)) || ((i > 18) && (i < 25)) || ((i > 31) && (i < 35)) || ((i > 35) && (i < 44))){

            tab[i]->proche.push_back(tab[i+6]);
        }
        if(((i > 8) && (i < 15)) || ((i > 24) && (i < 31)) || (i > 37)){

            tab[i]->proche.push_back(tab[i-6]);
        }
        if(((i > 2) && (i < 9)) || ((i > 18) && (i < 25)) || ((i > 31) && (i < 34)) || ((i > 40) && (i < 43))){

            tab[i]->proche.push_back(tab[i+7]);
        }
        if(((i > 9) && (i <16)) || ((i > 25) && (i < 32)) || ((i > 38) && (i < 41)) || (i > 47)){

            tab[i]->proche.push_back(tab[i-7]);
        }
        if(((i > 35) && (i < 38)) || ((i > 38) && (i < 41))){

            tab[i]->proche.push_back(tab[i+5]);
        }
        if(((i > 5) && (i < 8)) || ((i > 21) && (i < 24)) || ((i > 40) && (i < 43)) || ((i > 43) && (i < 46))){

            tab[i]->proche.push_back(tab[i-5]);
        }
        if(((i > 3) && (i < 6)) || ((i > 19) && (i < 22))){

            tab[i]->proche.push_back(tab[i-4]);
        }
        if((i > 24) && (i < 31)){

            tab[i]->proche.push_back(tab[i+18]);
        }
        if(i > 43){

            tab[i]->proche.push_back(tab[i-18]);
        }
        if((i > 25) && (i < 32)){

            tab[i]->proche.push_back(tab[i+19]);
        }
        if(i > 43){

            tab[i]->proche.push_back(tab[i-19]);
        }
        if((i > 9) && (i < 16)){

            tab[i]->proche.push_back(tab[i+22]);
        }
        if((i > 31) && (i < 38)){

            tab[i]->proche.push_back(tab[i-22]);
        }
        if((i > 8) && (i < 15)){

            tab[i]->proche.push_back(tab[i+23]);
        }
        if((i > 31) && (i < 38)){

            tab[i]->proche.push_back(tab[i-23]);
        }
    }
}

void Plateau::afficher(){

    for(int i = 0; i<50; i++){

            window.draw(plateau_graphique[i]);
    }
}

void Plateau::collision(){
    for(int i=0; i<50; i++){

        position_souris = Mouse::getPosition(window);
        if(plateau_graphique[i].getGlobalBounds().contains(position_souris.x,position_souris.y)){
            plateau_graphique[i].setFillColor(Color::Magenta);
            if(Mouse::isButtonPressed(Mouse::Left)){
                echo_case(i);
            }
        }else{
            plateau_graphique[i].setFillColor(Color(tab[i]->rouge,tab[i]->vert,tab[i]->bleu));
        }
    }
}



bool sprite_souris(Sprite sprite){
    position_souris = Mouse::getPosition(window);
    //cout << "Mouse.x :" << position_souris.x << "Mouse.y :" << position_souris.y << endl;
    return sprite.getGlobalBounds().contains(position_souris.x,position_souris.y);
}

void menu(){
    if(sprite_souris(jouer)){
                jouer.setColor(Color(100,250,100));
                if(Mouse::isButtonPressed(Mouse::Left)){
                    cout << "Le jeu commence" << endl;
                    interface = 2;
                }
            }else{
                jouer.setColor(Color(255,255,255));
            }

            if(sprite_souris(quitter)){
                quitter.setColor(Color(100,250,100));
                if(Mouse::isButtonPressed(Mouse::Left)){
                    window.close();
                }
            }else{
                quitter.setColor(Color(255,255,255));
            }
            window.draw(jouer);
            window.draw(quitter);
}

void jeu(){


}

int main()
{
    Plateau plateau;
    vector<CircleShape> plateau_graphique;
    plateau.liaison();

    Texture texture_jouer, texture_quitter;

    if (!texture_jouer.loadFromFile("image/button_jouer.png")){
        cout << "erreur";
    }
    if (!texture_quitter.loadFromFile("image/button_quit.png")){
        cout << "erreur";
    }

    jouer.setTexture(texture_jouer);
    jouer.setPosition(Vector2f(400, 400));
    quitter.setTexture(texture_quitter);
    quitter.setPosition(Vector2f(400,600));

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
        if(interface == 1){
            menu();
        }
        if(interface == 2){

            jeu();
            plateau.afficher();
            plateau.collision();

            if(Keyboard::isKeyPressed(Keyboard::Space)){

                window.draw(jouer);
                plateau.echo();
            }

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


