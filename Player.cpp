#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Player.h"

using namespace std;
using namespace sf;


//constructeur du joueur

    Player::Player(Statcard* stat,string name) {
        //pointeur vers les stats des cartes
        this->stat=stat;
        this->name=name;
        //initialisation des variables
        if(name=="Joueur 1"){
            mana=1;
            mana_dispo=1;
        }else{
            mana=0;
            mana_dispo=0;
        }
        mana_plus=0;

        displayMana=vector<Sprite>(12);
        deck = {7,57,35,7,17,7,57,35,70,17,7,57,35,70,17};
        //on place deux cartes dans la main
        hand.push_back(new Card (drawCardDeck(),stat,0));
        hand.push_back(new Card (drawCardDeck(),stat,1));

        towers=3;

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
    // Chargement des textures de mana disponible et mana vide pour la réserve de mana
        if(!manaAvailable.loadFromFile("image/mana_available.png")){
            cout << "erreur";
        }
        if(!manaEmpty.loadFromFile("image/mana_empty.png")){
            cout << "erreur";
        }
        if(!manaPlus.loadFromFile("image/mana_plus.png")){
            cout << "erreur";
        }
    }


    Player::~Player(){

        for(unsigned int i = 0; i < hand.size(); i++){

            delete hand[i];
        }
        hand.clear();
    }

    // ____________________ACTIVE____________________

    void Player::switchActive(bool active){
        if(active){
            addCardHand();
            augmentmana();
            displayHand();
            reset();
        }
        this->active = active;
    }

    bool Player::getActive(){
        return active;
    }

    string Player::getname(){
        return name;
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
            if (!deck.empty()){
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

    void Player::echoHand(RenderWindow* window){ // Collision avec les cartes

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
                cardselect.setPosition(100+i*150,760);
                window->draw(cardselect);
            }
            //si on pace sur une carte et qu'aucune autre n'est déjà balayé par la souris
            if((hand[i]->getimage().getGlobalBounds().contains(position_mouse.x,position_mouse.y))&&(hover==-1)){
                //changement de taille et de position de la carte quand on passe dessus
                a=100+i*150-75;
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
        for(unsigned int i=0; i<10+mana_plus;i++){
            if(i<10){
                if(i >= (10 - mana_dispo)){
                    mana.setTexture(manaAvailable);
                } else {
                    mana.setTexture(manaEmpty);
                }
            }else{
                mana.setTexture(manaPlus);
            }
            displayMana[i]=mana;
            displayMana[i].setPosition(80,120+i*50);
            window->draw(displayMana[i]);
        }
    }

    void Player::augmentmana(){ // Incrémentation du mana

        if(mana<10){
            mana++;
        }
        mana_dispo=mana;
        mana_plus=0;
        Vector2f position;
        for(unsigned int i=0;i<placed.size();i++){
            position=placed[i]->getimage().getPosition();
            if(position.x==783){
                if((position.y==134)||(position.y==699)){
                    mana_plus++;
                }
            }
        }
    }

//on vérifie qu'il nous reste assez de mana pour jouer la carte
    bool Player::checkmana(int i){
        unsigned int mana_spend=hand[i]->getmana();
        return mana_spend<=(mana_dispo+mana_plus);
    }

//on consomme le mana
    void Player::spendmana(int i){
        unsigned int mana_spend=hand[i]->getmana();
        if(mana_plus<mana_spend){
            mana_dispo+=(mana_plus-mana_spend);
            mana_plus=0;
        }else{
            mana_plus-=mana_spend;
        }
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


void Player::addCardPlaced (CardBoard* card, int i) {       //Ajoute une carte dans la main (proviens du deck)

    placed.push_back(card);
    if(i != -1){
        delete hand[i];
        hand.erase(hand.begin()+i);
    }
}


void Player::reset(){

    for(unsigned int i=0;i<placed.size();i++){


        placed[i]->resetstat();
    }
}


vector<CardBoard*> Player::getplaced(){

    return placed;
}


bool Player::destruct(CardBoard* card){

    for(unsigned int i=0;i< placed.size();i++){

        if(card == placed[i]){

            placed.erase(placed.begin()+i);
            addCardDiscard(card->getid());
            if(card->getname() == "Tour"){
                towers--;

                if(towers <= 1){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }

    return false;
}

//_________________________________DISCARD__________________

void Player::addCardDiscard(int i){
    discard.push_back(i);
}
