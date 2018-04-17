#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Console.h"

using namespace std;
using namespace sf;

Console::Console() : threadConsole(&Console::testCommand, this){
    threadConsole.launch();
}

void Console::testCommand() {
    bool active = true;
    while (active == true){
        cin >> command;
        if (command.front() == '/') {
            cout << "<Commande>" << endl;
        }
    }
}
