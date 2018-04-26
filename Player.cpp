#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Player.h"

using namespace std;
using namespace sf;

//constructeur du joueur
    Player::Player(Statcard* stat) {
        //pointeur vers les stats des cartes
        this->stat=stat;
        //initialisation des variables
        mana=1;
        mana_dispo=1;
        displayMana=vector<Sprite>(10);
        deck = {6,56,34,69,16};
        //on place deux cartes dans la main
        hand.push_back(new Card (drawCardDeck(),stat,0));
        hand.push_back(new Card (drawCardDeck(),stat,1));
        //aucune carte n'est sélectionnée
        select=-1;
        //importation de la font d'écriture
        if(!fontselect.loadFromFile("font/CloisterBlack.ttf")){
            cerr<<"Fichier font 'CloisterBlack.ttf' introuvable"<<endl;
        }
        //initialisation de l'indicateur pour savoir qu'elle carte est sélectionnée
        cardselect.setString("Select");
        cardselect.setFont(fontselect);
        cardselect.setCharacterSize(30);
        //importation des images pour le mana
        if(!manaAvailable.loadFromFile("image/mana_available.png")){
            cout << "erreur";
        }
        if(!manaEmpty.loadFromFile("image/mana_empty.png")){
            cout << "erreur";
        }
    }

    // ____________________ACTIVE____________________

    void Player::switchActive(bool active){
        this->active = active;
    }

    bool Player::getActive(){
        return active;
    }

    // ____________________DECK____________________

    void Player::shuffleDeck() {        //Mélange le deck du joueur
        srand(time(NULL));
        int exchange;
        for (unsigned int i = 0; i < deck.size(); i++) {
            int j = rand()%(deck.size());
            exchange = deck[j];
            deck[j] = deck[i];
            deck[i] = exchange;
        }
    }

    void Player::displayDeck() {        //Affiche le deck du joueur dans la console (pour des tests)
        cout << "Deck : " ;
        if (deck.empty() == true){
            cout << "Vide";
        } else {
            for (unsigned int i = 0; i < deck.size(); i++) {
                cout << deck[i];
                if (i < deck.size()-1) {
                    cout << ", ";
                }
            }
        }
        cout << endl << endl;
    }

    int Player::drawCardDeck() {        //Sortir une carte du deck, retourne la valeur de la première carte et la retire du deck
        int card;
        if (deck.empty() == false) {
            card = deck[0];
            deck.erase(deck.begin());
        }
        return card;
    }

    int Player::copyCardDeck() {        //Copier une carte du deck, retourne la valeur de la première carte (reste dans le deck)
        int card;
        if (deck.empty() == false) {
            card = deck[0];
        }
        return card;
    }

    //____________________HAND____________________

    void Player::addCardHand () {               //Ajoute une carte dans la main (proviens du deck)
        if (hand.size() < 20){
            if (deck.empty() == false){
                hand.push_back(new Card(drawCardDeck(),stat,hand.size()-1));
            } else {
                cout << "! Le deck est vide" << endl << endl;
            }
        } else {
            cout << "! Nombre de carte max atteint" << endl << endl;
        }
    }

    void Player::displayHand() {                //Affiche la main du joueur dans la console
        cout << "Main: " ;
        for (unsigned int i = 0; i < hand.size(); i++) {
            cout << hand[i]->getname();
            if (i < hand.size()-1) {
                cout << ", ";
            }
        }
        cout << endl << endl;
    }

    //affichage des cartes de la main

    void Player::echoHand(RenderWindow* window){
        //variable pour savoir sur qu'elle carte on passe, une seule à la fois
        int hover=-1;
        Vector2f z;
        z.x=1;
        z.y=1;
        int a=0;
        int b=600;
        //on parcoure toutes les cartes de la main
        for(unsigned int i=0; i<hand.size();i++){
            //on récupère la position de la souris
            Vector2i position_mouse = Mouse::getPosition(*window);
            //si une carte est sélectionné on affiche un indicateur au dessus de celle ci "select"
            if(hand[i]->getselect()){
                cardselect.setPosition(300+i*150,760);
                window->draw(cardselect);
            }
            //si on pace sur une carte et qu'aucune autre n'est déjà balayé par la souris
            if((hand[i]->getimage().getGlobalBounds().contains(position_mouse.x,position_mouse.y))&&(hover==-1)){
                //changement de taille et de position de la carte quand on passe dessus
                a=300+i*150-75;
                hand[i]->hovercard(a,b,z);
                //on sauvegarde la carte sur laquelle la souris est
                hover=i;
                // si on clique
                if(Mouse::isButtonPressed(Mouse::Left)){
                    //la carte est sélectionnée
                    select=hover;
                    hand[hover]->echocard(window);
                    //on déselectionnes les autres cartes
                    for(unsigned int j=0; j<hand.size();j++){
                        hand[j]->setselect(false);
                    }
                    //on la sélectionnnes
                    hand[hover]->setselect(true);
                }
                //si on clique droit la carte est déselectionnées
                if(Mouse::isButtonPressed(Mouse::Right)){
                    select=-1;
                    hand[hover]->setselect(false);
                }
            }else{
                //on ne passe plus sur la carte elle reprends sa taille initiale
                hand[i]->nothovercard(i);
            }
            //on affiche les cartes
            hand[i]->echocard(window);
        }
    }
//on affiche le mana restant est celui consommé
    void Player::stockMana(RenderWindow* window){
        Sprite mana;
        for(unsigned int i=0; i<10;i++){
            if(i >= (10 - mana_dispo)){
                mana.setTexture(manaAvailable);
                displayMana[i]=mana;
            } else {
                mana.setTexture(manaEmpty);
                displayMana[i]=mana;
            }
            displayMana[i].setPosition(80,120+i*50);
            window->draw(displayMana[i]);
        }
    }
//àchaque tour on augmente le mana disponible
    void Player::augmentmana(){
        if(mana_dispo<10){
            mana++;
            mana_dispo=mana;
        }
        if(mana_dispo == 10){
            mana_dispo=mana;
        }
    }
//on vérifie qu'il nous reste assez de mana pour jouer la carte
    bool Player::checkmana(int i){

        return hand[i]->getmana()<=mana_dispo;
    }
//on consomme le mana
    void Player::spendmana(int i){
        mana_dispo-=hand[i]->getmana();
    }
//on récupère l'id de la carte sélectionnée
    int Player::getselect(){
        return select;
    }
//on déselectionnes
    void Player::deselect(){
        select=-1;
    }
//_______________________________PLACED______________________

Card* Player::getcard(int i){
    return hand[i];
}

void Player::addCardPlaced (CardBoard* card,int i) {       //Ajoute une carte dans la main (proviens du deck)
        placed.push_back(card);
        hand.erase(hand.begin()+i);
}

void Player::echoPlaced(){

}
