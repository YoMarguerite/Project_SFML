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
    string name;
    Statcard* stat;
    bool active;
    vector<unsigned int> deck;
    vector<unsigned int> discard;
    vector<Card*> hand;
    vector<Sprite> displayMana;
    // Ce sera pas vector<Card*> placed; mais peut-être vector<Cardboard*>placed;
    vector<CardBoard*> placed;
    unsigned int mana;
    unsigned int mana_dispo;
    int select;
    Text cardselect;
    Font fontselect;
    Texture manaEmpty;;
    Texture manaAvailable;
    public:

    Player(Statcard* stat,string name);

    // ____________________ACTIVE____________________

    void switchActive(bool active);

    bool getActive();

    string getname();

    // ____________________DECK____________________

    void shuffleDeck();       //Mélange le deck du joueur

    void displayDeck();       //Affiche le deck du joueur dans la console (pour des tests)

    int drawCardDeck();        //Sortir une carte du deck, retourne la valeur de la première carte et la retire du deck

    int copyCardDeck();        //Copier une carte du deck, retourne la valeur de la première carte (reste dans le deck)


    //____________________DISCARD____________________

    void addCardDiscard(int i);

    //____________________HAND____________________

    void addCardHand ();                //Ajoute une carte dans la main (proviens du deck)

    void displayHand();                //Affiche la main du joueur dans la console

    void echoHand(RenderWindow* window);

    int getselect();

    void deselect();

    //____________________PLACED__________________

    Card* getcard(int i);

    vector<CardBoard*> getplaced();

    void destruct(int i);

    void addCardPlaced (CardBoard* card,int i);

    void reset();

    //____________________MANA____________________

    void stockMana(RenderWindow* window);

    void augmentmana();

    bool checkmana(int i);

    void spendmana(int i);
};

#endif // PLAYER_H_INCLUDED
