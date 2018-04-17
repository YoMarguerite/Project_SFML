#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main () {
  string line;
  string delimiter;
  ifstream filecards ("unity.csv");
  vector < string > datacard;

  // Si mon fichier est ouvert
  if (filecards.is_open()){
    // Tant qu'on a pas parcouru tout le fichier
    while ( getline (filecards,line) ){
      cout << line << '\n';
    }

    // Fermer le fichier
    filecards.close();
  }

  else {
        cerr << "Impossible d'\ouvrir le fichier" << endl;
  }

  return 0;
}
