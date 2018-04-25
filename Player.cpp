#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Player.h"

using namespace std;
using namespace sf;

    Player::Player(Statcard* stat) {
        this->stat=stat;
        mana=1;
        mana_dispo=1;
        displayMana=vector<Sprite>(10);
        deck = {6,56,34,69,17};
        hand.push_back(new Card (drawCardDeck(),stat,0));
        hand.push_back(new Card (drawCardDeck(),stat,1));
        select=-1;
        if(!fontselect.loadFromFile("font/CloisterBlack.ttf")){
            cerr<<"Fichier font 'CloisterBlack.ttf' introuvable"<<endl;
        }

        cardselect.setString("Select");
        cardselect.setFont(fontselect);
        cardselect.setCharacterSize(30);

        if(!manaAvailable.loadFromFile("image/mana_available.png")){
            cout << "erreur";
        }
        if(!manaEmpty.loadFromFile("image/mana_empty.png")){
            cout << "erreur";
        }
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

    void Player::echoHand(RenderWindow* window){
        int hover=-1;
        Vector2f z;
        z.x=1;
        z.y=1;
        int a=0;
        int b=600;
        cout<<hand.size()<<"taille dans le echo"<<endl;
        for(unsigned int i=0; i<hand.size();i++){

            Vector2i position_mouse = Mouse::getPosition(*window);
            if(hand[i]->getselect()){
                cardselect.setPosition(300+i*150,760);
                window->draw(cardselect);
            }
            if((hand[i]->getimage().getGlobalBounds().contains(position_mouse.x,position_mouse.y))&&(hover==-1)){
                a=300+i*150-75;
                hand[i]->hovercard(a,b,z);
                hover=i;
                if(Mouse::isButtonPressed(Mouse::Left)){
                    select=hover;
                    hand[hover]->echocard(window);
                    for(unsigned int j=0; j<hand.size();j++){
                        hand[j]->setselect(false);
                    }
                    hand[hover]->setselect(true);
                }
                if(Mouse::isButtonPressed(Mouse::Right)){
                    select=-1;
                    hand[hover]->setselect(false);
                }
            }else{
                hand[i]->nothovercard(i);
            }
            hand[i]->echocard(window);
        }
    }

    void Player::stockMana(RenderWindow* window){
        Sprite mana;
        cout<<mana_dispo<<endl;
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

    void Player::augmentmana(){
        if(mana_dispo<10){
            mana++;
            mana_dispo=mana;
        }
        if(mana_dispo == 10){
            mana_dispo=mana;
        }
    }

    bool Player::checkmana(int i){

        return hand[i]->getmana()<=mana_dispo;
    }

    void Player::spendmana(int i){
        cout<<"ton mana .... :"<<mana_dispo<<endl;
        cout<<"son mana .... :"<<hand[i]->getmana()<<endl;
        mana_dispo-=hand[i]->getmana();
    }

    int Player::getselect(){
        return select;
    }

    void Player::deselect(){
        select=-1;
    }
//_______________________________PLACED______________________

Card* Player::getcard(int i){
    return hand[i];
}

void Player::addCardPlaced (CardBoard* card,int i) {               //Ajoute une carte dans la main (proviens du deck)
        placed.push_back(card);
        hand.erase(hand.begin()+i);
}

void Player::echoPlaced(){

}
