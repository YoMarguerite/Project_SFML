#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Statcard.h"

Statcard::Statcard(){
    string line;
    char letter;
    int lengh=80;
    ifstream file ("card_export.csv",ios::in);
    card=vector<vector<string>>(lengh);
    int index=0;
    int id=0;

    for(int i = 0; i<lengh;i++){

        card[i]=vector<string>(10);
    }

      // Si mon fichier est ouvert
      if (file.is_open()){
      // Tant qu'on a pas parcouru tout le fichier
        while ( getline (file,line) ){

          cout << line << endl;
          lengh=line.size();
          id=0;
          for(int i=0; i<lengh; i++){
                letter=line[i];
                if(letter==';'){
                    id++;
                }else{
                    card[index][id]=card[index][id]+letter;
                }
          }

          for(int i=0; i<10; i++){
                cout << card[index][i] << " ";
          }
          cout<<endl;
          index++;
        }
        // Fermer le fichier

        file.close();
      }

      else {

            cerr << "Impossible d'ouvrir le fichier" << endl;
      }
}
