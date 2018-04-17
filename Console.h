#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED
#include <iostream>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

class Console{

private:
    string command;
    bool active;
public:
    Console();
    void testCommand();
    Thread threadConsole;
};
#endif // CONSOLE_H_INCLUDED
