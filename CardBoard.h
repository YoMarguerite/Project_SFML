#ifndef CARTEPLATEAU_H_INCLUDED
#define CARTEPLATEAU_H_INCLUDED
#include "Card.h"

using namespace std;


class CardBoard{
private:
    int id;
    int place;
    string camp;
    string quality;
    string name;
    string type;
    string effectText;
    Texture dessin;
    Sprite image;
    Font font;
    Text Vie;
    Text Attaque;
    Text Moving;
    Vector2f position;
    int anim;
    bool select;
    string family;
    int life;
    int damage;
    int lim_move;
    int movement;
    bool sleep;
    int build;
    int lim_coup;
    int nbcoup;

public:
    CardBoard(Card* card,Vector2f position,string camp);
    void echo();
    Sprite getimage();
    Text getvie();
    Text getattaque();
    Text getmoving();
    Vector2f getposition();
    void setposition(Vector2f position);
    int getid();
    int getmovement();
    int getdamage();
    int getlife();
    int getcoup();
    int getplace();
    int getbuild();
    void setplace(int i);
    void setmovement();
    void setcoup();
    void setbuild();
    void resetstat();
    void setimageposition(Vector2f position);
    string getcamp();
    string getname();
    bool takedamage(CardBoard* opponent);
    int getanim();
    void setanim();
    void duringanim();

};
#endif // CARTEPLATEAU_H_INCLUDED
