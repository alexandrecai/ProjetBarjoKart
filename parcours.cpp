#include "parcours.hpp"
#include <fstream>
#include <iostream>

using namespace std;

Parcours::Parcours(){}

Parcours::~Parcours(){
    std::cout << "Destructeur Parcours" << endl;
}


void Parcours::trouverFin(vector<vector<int> > _circuit, int x, int y){

    std::vector<std::pair<int,int> > voisins;
    vector<std::pair<int,int> > voisinsXY = getVoisins(_circuit, x, y);
  
    _circuit[y][x] = 1;

    for (std::pair<int,int>  voisin : voisinsXY){
        voisins.push_back(voisin);
    }

    while (voisins.size() > 0){

        for (int i = 0; i < _circuit.size(); i++){
            for (int j = 0; j < _circuit[i].size(); j++){
                cout << _circuit[i][j] << " ";
            }
            cout << endl;
        }
        cout << "voisins : " << voisins.size() << endl;

        pair<int,int> voisin = voisins.back();
        voisins.pop_back();
        if (_circuit[voisin.second][voisin.first] == 9){
            cout << "succes : arrivee atteinte" << endl;
            cout << "arrivee atteinte en " << voisin.first << "," << voisin.second << endl;
            for (int i = 0; i < _circuit.size(); i++){
                for (int j = 0; j < _circuit[i].size(); j++){
                    cout << _circuit[i][j] << " ";
                }
                cout << endl;
            }
            return;
        }
        else {
            _circuit[voisin.second][voisin.first] = 1;
            voisinsXY = getVoisins(_circuit, voisin.first, voisin.second);
            for (pair<int,int>  voisin : voisinsXY){
                voisins.push_back(voisin);
            }
        }
    }
}

bool Parcours::positionValide(vector<vector<int> > _circuit, int x, int y){
  //cout << "valeur x : " << x << " valeur y : " << y << endl;
  //cout << (x < _circuit.size()) << endl;
  if(x < 0 || y < 0 || x > _circuit.size()-1 || y >_circuit.size()-1){
        cout << "erreur : position invalide : " << x << "_______" << y << endl;
        return false;

    }
    else if (_circuit[y][x] == 2)
    {
      cout << "erreur : mur "<< endl;
      return false;
    }
    else if (_circuit[y][x] == 1)
    {
      cout << "erreur : déjà passé" << endl;
      return false;
    }
    else {
      return true;
    }
}

vector<pair<int,int> > Parcours::getVoisins(vector<vector<int> > _circuit, int x, int y){
  vector<pair<int,int> > voisinsXY;
  if (positionValide(_circuit, x+1, y)){
    voisinsXY.push_back(make_pair(x+1,y));
  }
  if(positionValide(_circuit, x-1, y)){
    voisinsXY.push_back(make_pair(x-1,y)); 
  }
  if(positionValide(_circuit, x, y+1)){
    voisinsXY.push_back(make_pair(x,y+1)); 
  }
  if(positionValide(_circuit, x, y-1)){
    voisinsXY.push_back(make_pair(x,y-1)); 
  }
  return voisinsXY;

}





///////////////////////
//   Algorithme de test permettant de parcourir le circuit basique
///////////////////////  
void Parcours::CheminAlaMain(){
    std::ofstream myFile ("chemin.bin", std::ios::out | std::ios::binary);
    int vitesse = 1;
    int valeurJ = 0;
    int j;
    for(int i = 0; i<99; i++){
        int baseJ = i;
        for(int j = baseJ; j < (baseJ + 1); j++){
            valeurJ = baseJ ;
            myFile.write (reinterpret_cast<const char *>(&i), sizeof(i));
            myFile.write (reinterpret_cast<const char *>(&valeurJ), sizeof(valeurJ));
            std::cout << "(" << i << "," << valeurJ << ")" <<'\n';
        }

        baseJ = baseJ + j;
    }
    myFile.close();
}
