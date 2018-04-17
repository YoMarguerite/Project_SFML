#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h"

    Player::Player(Statcard* stat) {
        this->stat=stat;
        mana_dispo=1;
        deck = {6,52,35,59,17}; //importation du deck préconstruit en .csv
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

    //____________________DISCARD____________________



    //____________________HAND____________________

    void Player::addCardHand () {               //Ajoute une carte dans la main (proviens du deck)
        if (hand.size() < 20){
            if (deck.empty() == false){
                hand.push_back(new Card(drawCardDeck(),stat));
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

    void Player::echoHand(RenderWindow* window){
        for(unsigned int i=0; i<hand.size();i++){
            hand[i]->echocard(window,i);
        }
    }

    void Player::augmentmana(){
        if(mana_dispo<10){
            mana_dispo++;
        }
    }
