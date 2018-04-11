#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <vector>
#include "Statcard.h"
#include "Card.h"

using namespace std;

class Player{
    private:
    Statcard* stat;
    vector<unsigned int> deck;
    vector<unsigned int> discard;
    vector<Card*> hand;
    // Ce sera pas vector<Card*> placed; mais peut-être vector<Cardboard*>placed;
    vector<Card*> placed;
    unsigned int mana_dispo;
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

    //____________________MANA____________________

    void augmentmana();
};

#endif // PLAYER_H_INCLUDED
