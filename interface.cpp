#include "interface.hpp"

using namespace std;

Interface::Interface(){

}

vector<string> Interface::getInfosInterface(){
  string toml;
  string png;
  vector<string> valeurs;

  cout << "Veuillez entrer le nom du fichier png : " << endl;
  cin >> png;
  cout << "Veuillez entrer le nom du fichier toml : " << endl;
  cin >> toml;

  valeurs.push_back(png);
  valeurs.push_back(toml);

  return valeurs;
}

// destructeur
Interface::~Interface(){
  cout<<"Destruction de Interface" <<endl;
}