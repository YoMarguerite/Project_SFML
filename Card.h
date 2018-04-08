#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED


using namespace std;

class Card{
    //ATTRIBUTS
    private:
    int id;
    short type;         //0:unité   1:batiment  2:sort
    string name;
    short quality;      //0:commun  1:rare      2:epique    3:legendaire
    //image
    int mana;
    string effectText;

    public:
    Card(int id);

    void importStats();

};

class Placeable : public Card {
    private:
    int family;         //id de la famille
    int life;
    int damage;
};

class Unity : public Placeable {
    private:
    int movement;
    bool sleep;
};

class Building : public Placeable{
    int build;
};

class Spell : public Card {

};


#endif // CARD_H_INCLUDED
