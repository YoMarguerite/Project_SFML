#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "Statcard.h"

using namespace std;
using namespace sf;


//constructeur de la class contenant les stats des cartes

Statcard::Statcard(){
    string line;
    char letter;
    int lengh=81;
    ifstream file ("card_export.csv",ios::in);
    card=vector<vector<string>>(lengh);
    image=vector<Texture>(lengh);
    int index=0;
    int id=0;
    //importation des stats
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
        //importation des images des cartes
        Texture texture;
        for(unsigned int i=0; i<card.size();i++){
            if(!texture.loadFromFile("image/"+card[i][2]+".png")){
                cerr<<"Fichier image "+card[i][2]+".png introuvable"<<endl;
            }else{
                cout<<"c'est bon : "+card[i][2]<<endl;

            }
            image[i]=texture;
        }
      }

      else {

            cerr << "Impossible d'ouvrir le fichier" << endl;
      }
}
//on r�cup�re l'image d'une carte
Texture Statcard::getimage(int id){
    return image[id];
}
//on r�cup�re les stats d'une carte
vector<string> Statcard::getstats(int id){
    return card[id];
}
