#include "recupParam.hpp"
#include "circuit.hpp"
#include <fstream>
#include <stdlib.h>

using namespace std;

void CheminALaMain(){
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

int main() {

  // Tests montrants le fonctionnement de la classe permettant de récupérer les paramètres issus du .toml .

  //Parametres de configuration
  string paramFile = "basique.toml";
  string circuit = "basique.png";


  RecupParam *recupParam = new RecupParam();
  Circuit *circuitTest = new Circuit(circuit);


 // méthode obligatoire - permet "lire" le .toml et d'en extraire les paramètres
  (*recupParam).setVarFromFile(paramFile);

  //getters
  int acc_max = (*recupParam).getAccelerationMax();
  std::vector<int> couleur_arrivee = (*recupParam).getRgbArrivee();


  //Recuperation coordonnées depart
  std::map<std::string, int> depart = (*recupParam).getCoordonneesDepart();
  int x_depart = depart["x"];
  int y_depart = depart["y"];


  // Generation du circuit sous forme de tableau de vecteurs a 2 dimensions
  vector<vector<int> > circuit_ = (*circuitTest).generateCircuit(circuit, (*recupParam).getRgbArrivee(), x_depart, y_depart);

for(int i = 0; i < circuit_.size(); i++){
        for(int j = 0; j < circuit_[i].size(); j++){
            cout << circuit_[i][j];
        }
        cout << endl;
    }
  


  CheminALaMain();

  int lecture;

 
  std::ifstream myFileToRead ("chemin.bin", std::ios::out | std::ios::binary);
  myFileToRead.read (reinterpret_cast<char *>(&lecture), sizeof(lecture));
  std::cout << (int)lecture << ": lec " << std::endl;
 

  delete recupParam;

  return EXIT_SUCCESS;
}
