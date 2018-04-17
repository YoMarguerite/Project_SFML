#ifndef STATCARD_H_INCLUDED
#define STATCARD_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;

class Statcard{
private:
    vector<vector<string>>card;
    vector<Texture>image;
public:
    Statcard();
    Texture getimage(int id);
    vector<string> getstats(int id);
};

#endif // STATCARD_H_INCLUDED
