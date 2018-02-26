#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "class.h"


using namespace std;
using namespace sf;

// déclaration en dehors du main pour pouvoir les utiliser dans tout le programme
// sprite des boutons du menu
Sprite jouer, quitter;
// fenêtre principale avec sa taille et son nom
RenderWindow window(VideoMode(1200,800), "LES TOURS");
// Vector2i est l'équivalent d'un point il peut contenir deux valeurs, plus tard on lui affectera les coordonnées de la souris
Vector2i position_souris;
// variable définissant si on est sur le menu ou dans une partie
int interface = 1;



// class pour créer les différentes cases du plateau de manière indépendante
class Emplacement{

public:
    int numero;
    // couleur enregistrée pour chaque case
    int rouge;
    int vert;
    int bleu;
    // effet sur la case
    bool vide;
    bool mana;
    bool poison;
    // définition de la case
    string camp;
    string type;
    // case adjacente
    vector<Emplacement*> proche;

    //constructeur et autre méthode
    Emplacement(int id);
    vector<Emplacement*>& get();

};


//constructeur
Emplacement::Emplacement(int id){

    numero = id;

    // en fonction de l'id reçus on va définir cet objet, lui affecter une couleur un camp et un type
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
    }else if(id < 34){
        camp = "Neutre";
        if((id  == 22) || (id == 27)){
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
    }else{
        camp = "Joueur 2";
        if(id > 46){
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
    }
}


// cette fonction retourne le vecteur contenant les adresses des cases adjacentes
vector<Emplacement*>& Emplacement::get(){

    return proche;
}


// class pour créer le plateau en lui même
class Plateau{

private:
    // vecteur qui va contenir toutes les cases du plateau
    vector<Emplacement*> tab;

    // vecteur qui va contenir les hexagones pour chaque case
    //(on peut retrouver l'hexagone d'une case car ils sont rangés dans le même ordre sur chaque vecteur)
    vector<CircleShape> plateau_graphique;

public:
    // constructeur
    Plateau();
    // destructeur
    ~Plateau();
    // autre méthode ou fonction
    void echo();
    void echo_case(int id);
    void liaison();
    vector<Emplacement*>& get();
    void afficher();
    void collision();

};

// constructeur
Plateau::Plateau(){

// création de chaque case puis on conserve leurs adresses dans le vecteur tab
    for(int i=0; i<50 ; i++){
        Emplacement* pointeur;
        pointeur = new Emplacement(i);
        tab.push_back(pointeur);
    }

// création de chaque hexagone avec leurs positions
    int taille=plateau_graphique.size();
    int i=1;
    int posx=400, posy=40, decy=136;

    while(taille<50){

        if((taille==3) || (taille==9) || (taille==16) || (taille==22) || (taille==25)
           || (taille==28) || (taille==34) || (taille==41) || (taille==47)){
            i=1;
        }
        if((taille == 3) || (taille == 9) || (taille == 16) || (taille == 22)
           || (taille == 28) || (taille == 34) || (taille == 41) || (taille == 47)){
            posx+=60;
        }
        if((taille==9) || (taille==22) || (taille==34)){
            posy=40;
        }
        if((taille==3) || (taille==16) || (taille==28) ||(taille==41)){
            posy=74;
        }
        if(taille==25){
            posy=312;
        }
        if(taille == 3){
            decy=68;
        }
        if(taille == 47){
            posy=40;
            decy=136;
        }

        plateau_graphique.push_back(hex(posx,i*decy+posy));
        taille=plateau_graphique.size();
        i++;
    }
}

// destructeur du plateau et de chaque case
Plateau::~Plateau(){
    int taille = tab.size();
    for(int i = 0; i<taille-1; i++){
        delete tab[i];
    }
}

//affichage du contenu de tab
void Plateau::echo(){

    int taille = tab.size();
    cout << "Vector[" << taille << "] : ";
    for(int i = 0 ; i < taille; i++){
        cout << tab[i] << " ";
    }
    cout << endl;
}

// affichage d'une case précise identifiée par son id
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

// retourne les valeurs de tab donc les adresses de chaque case
vector<Emplacement*>& Plateau::get() {

  return tab;

}

// définie les liaisons de chaque case avec les cases adjacentes
void Plateau::liaison(){
    int taille = tab.size();
    for(int i = 0; i < taille; i++){

            if(((i > 9) && (i < 25) && (i != 22)) || ((i > 31) && (i < 47) && (i != 34))){

                tab[i]->proche.push_back(tab[i-7]);
            }
            if((i > 7) && (i < 48) && (i != 15) && (i != 40)){

                tab[i]->proche.push_back(tab[i-6]);
            }
            if((i == 6) || (i == 7) || ((i > 24) && (i < 30) && (i != 27)) || (i == 47) || (i == 48)){

                tab[i]->proche.push_back(tab[i-5]);
            }
            if((i == 4) || (i == 5) || (i == 48) || (i == 49)){

                tab[i]->proche.push_back(tab[i-4]);
            }
            if((i == 3) || (i == 49)){

                tab[i]->proche.push_back(tab[i-3]);
            }
            if((i > 3) && (i !=9) && (i != 16) && (i != 22) && (i != 25) && (i != 28) && (i != 34) && (i != 41) && (i < 47)){

                tab[i]->proche.push_back(tab[i-1]);
            }
            if((i > 2) && (i !=8) && (i != 15) && (i != 21) && (i != 24) && (i != 27) && (i != 33) && (i != 40) && (i < 46)){

                tab[i]->proche.push_back(tab[i+1]);
            }
            if((i == 0) || (i == 46)){

                tab[i]->proche.push_back(tab[i+3]);
            }
            if((i == 0) || (i == 1) || (i == 44) || (i == 45)){

                tab[i]->proche.push_back(tab[i+4]);
            }
            if((i == 1) || (i == 2) || ((i > 19) && (i < 25) && (i != 22)) || (i == 42) || (i == 43)){

                tab[i]->proche.push_back(tab[i+5]);
            }
            if((i > 1) && (i < 42) && (i != 9) && (i != 34)){

                tab[i]->proche.push_back(tab[i+6]);
            }
            if(((i > 2) && (i < 18) && (i != 15)) || ((i > 24) && (i < 40) && (i != 27))){

                tab[i]->proche.push_back(tab[i+7]);
            }
    }
}

// affichage sur l'écran des hexagones des cases
void Plateau::afficher(){

    for(int i = 0; i<50; i++){

            window.draw(plateau_graphique[i]);
    }
}

// gestion de la collision de chaque case avec la souris
void Plateau::collision(){
    // on fait défiler tous les hexagones
    for(int i=0; i<50; i++){
        // on récupère les coordonnées de la souris
        position_souris = Mouse::getPosition(window);
        // on vérifie que l'hexagone contient la souris
        if(plateau_graphique[i].getGlobalBounds().contains(position_souris.x,position_souris.y)){
            // si c'est le cas on change sa couleur en magenta
            plateau_graphique[i].setFillColor(Color::Magenta);
            // si on clique les caractéristiques de la case s'affiche
            if(Mouse::isButtonPressed(Mouse::Left)){
                echo_case(i);
            }
        }else{
            // si l'hexagone ne contient pas la souris on lui redonne sa couleur d'origine
            plateau_graphique[i].setFillColor(Color(tab[i]->rouge,tab[i]->vert,tab[i]->bleu));
        }
    }
}


// on vérifie que le sprite contient la souris
bool sprite_souris(Sprite sprite){
    position_souris = Mouse::getPosition(window);
    //cout << "Mouse.x :" << position_souris.x << "Mouse.y :" << position_souris.y << endl;
    return sprite.getGlobalBounds().contains(position_souris.x,position_souris.y);
}

// fonction pour gérer le menu
void menu(){
    // si le bouton jouer contient la souris
    if(sprite_souris(jouer)){
            // on change sa couleur
            jouer.setColor(Color(100,250,100));
            // si on clique
            if(Mouse::isButtonPressed(Mouse::Left)){
                // le jeu commence et on change d'interface
                cout << "Le jeu commence" << endl;
                interface = 2;
            }
        }else{
            // sinon on lui redonne sa couleur d'origine
            jouer.setColor(Color(255,255,255));
        }

        // si le bouton quitter contient la souris
        if(sprite_souris(quitter)){
            // on change sa couleur
            quitter.setColor(Color(100,250,100));
            // si on clique la fenêtre se ferme
            if(Mouse::isButtonPressed(Mouse::Left)){
                window.close();
            }
        }else{
            // sinon le bouton reprend sa couleur
            quitter.setColor(Color(255,255,255));
        }
        // on dessine le bouton jouer et quitter sur la fenêtre
        window.draw(jouer);
        window.draw(quitter);
}

// fonction contenant le futur code du jeu
void jeu(){


}

int main()
{
    // limite les fps pour ne pas faire surchauffer la carte graphique
    window.setFramerateLimit(60);
    // création de l'objet plateau et des cases
    Plateau plateau;
    plateau.liaison();


    // on définit des textures et on leur donne une image
    Texture texture_jouer, texture_quitter;

    if (!texture_jouer.loadFromFile("image/button_jouer.png")){
        cout << "erreur";
    }
    if (!texture_quitter.loadFromFile("image/button_quit.png")){
        cout << "erreur";
    }
    //on donne cette texture aux sprites, et on leur donne des coordonnées
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
        // on vérifie sur qu'elle interface on est menu ou en jeu
        if(interface == 1){
            // execution du menu
            menu();
        }
        if(interface == 2){

            // execution du jeu
            jeu();
            plateau.afficher();
            plateau.collision();

            // condition inutile c'était juste pour mes tests
            if(Keyboard::isKeyPressed(Keyboard::Space)){

                window.draw(jouer);
                plateau.echo();
            }

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


