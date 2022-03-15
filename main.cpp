#include "recupParam.hpp"
#include "circuit.hpp"
#include <fstream>
#include <stdlib.h>

using namespace std;

void CheminALaMain(){
    std::ofstream myFile ("chemin.bin", std::ios::out | std::ios::binary);
    int vitesse = 1;
    int valeurJ = 0;
    int baseJ = 0;
    int x = 2;
    int y = 2;
    for(int i = 0; i<49; i++){

        myFile.write (reinterpret_cast<const char *>(&x), sizeof(x));
        myFile.write (reinterpret_cast<const char *>(&y), sizeof(y));
        std::cout << "(" << x << "," << y << ")" <<'\n';

    }
    x = 1;
    y = 1;
    myFile.write (reinterpret_cast<const char *>(&x), sizeof(x));
    myFile.write (reinterpret_cast<const char *>(&y), sizeof(y));
    std::cout << "(" << x << "," << y << ")" <<'\n';
    myFile.close();
}

int main() {

  // Tests montrants le fonctionnement de la classe permettant de récupérer les paramètres issus du .toml .

  //Parametres de configuration
  string paramFile = "basique.toml";
  string circuit = "basique.png";


  RecupParam *recupParam = new RecupParam();
  Circuit *circuitTest = new Circuit(circuit);

  (*circuitTest).getCarte();

  // méthode obligatoire - permet "lire" le .toml et d'en extraire les paramètres
  (*recupParam).setVarFromFile(paramFile);

  //getters
  int acc_max = (*recupParam).getAccelerationMax();

  std::vector<int> couleur_arrivee = (*recupParam).getRgbArrivee();

  std::map<std::string, int> depart = (*recupParam).getCoordonneesDepart();

  std::cout << std::endl;

  CheminALaMain();

  int lecture;

  std::ifstream myFileToRead ("chemin.bin", std::ios::out | std::ios::binary);
  myFileToRead.read (reinterpret_cast<char *>(&lecture), sizeof(lecture));
  std::cout << (int)lecture << std::endl;


  delete recupParam;

  return EXIT_SUCCESS;
}
