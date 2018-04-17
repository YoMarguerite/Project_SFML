#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <vector>
#include <SFML/Graphics.hpp>
#include "Statcard.h"
#include "Card.h"
#include "CardBoard.h"

using namespace std;
using namespace sf;

class Player{
    private:
    Statcard* stat;
    vector<unsigned int> deck;
    vector<unsigned int> discard;
    vector<Card*> hand;
    // Ce sera pas vector<Card*> placed; mais peut-être vector<Cardboard*>placed;
    vector<CardBoard*> placed;
    unsigned int mana;
    unsigned int mana_dispo;
    int select;
    Text cardselect;
    Font fontselect;
    public:

    Player(Statcard* stat);

    // ____________________DECK____________________

    void shuffleDeck();       //Mélange le deck du joueur

    void displayDeck();       //Affiche le deck du joueur dans la console (pour des tests)

    int drawCardDeck();        //Sortir une carte du deck, retourne la valeur de la première carte et la retire du deck

    int copyCardDeck();        //Copier une carte du deck, retourne la valeur de la première carte (reste dans le deck)


    //____________________DISCARD____________________



    //____________________HAND____________________

    void addCardHand ();                //Ajoute une carte dans la main (proviens du deck)

    void displayHand();                //Affiche la main du joueur dans la console

    void echoHand(RenderWindow* window);

    int getselect();

    //____________________PLACED__________________

    void addCardPlaced (int i);

    //____________________MANA____________________

    void augmentmana();
};

#endif // PLAYER_H_INCLUDED
