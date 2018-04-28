#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include<SFML/Graphics.hpp>



using namespace std;

using namespace sf;



class Menu {

    private:
        Texture textureBkg;
        Sprite bckg;
        Texture texture_play;
        Texture texture_leave;
        Sprite play;
        Sprite leave;
        Text titleGame;
        Font title;

    public:

        Menu(Vector2f windowsize);

        void display(RenderWindow* window,int* interface);

};



#endif // MENU_H_INCLUDED
