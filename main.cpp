#include "recupParam.hpp"
#include "circuit.hpp"
#include "parcours.hpp"
#include "dijkstra.hpp"
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
  string paramFile = "prairie.toml";
  string circuit = "prairie.png";


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


  //A modifier pour changer la trajectoire
  vector<int> accels = {2,0,3,1,4,2,5,3,6,4,7,5,8,6,9,7,9,9,9,11,9,13,10,14,9,13,9,11};


  // Generation du circuit sous forme de tableau de vecteurs a 2 dimensions
  vector<vector<int> > circuit_ = (*circuitTest).generateCircuit(circuit, (*recupParam).getRgbArrivee(), x_depart, y_depart);

  //Generation du chemin sur le circuit
  //circuit_ = (*circuitTest).ajoutChemin(circuit_,accels,x_depart,y_depart,acc_max);

  // Parcours en profondeur
//  Parcours *parcours = new Parcours();
//  (*parcours).trouverFin(circuit_,x_depart,y_depart);


  // Dijkstra
  int myGraph[6][6]={
        {0, 1, 2, 0, 0, 0},
        {1, 0, 0, 5, 1, 0},
        {2, 0, 0, 2, 3, 0},
        {0, 5, 2, 0, 2, 2},
        {0, 1, 3, 2, 0, 1},
        {0, 0, 0, 2, 1, 0}};

	Dijkstra *dijkstra = new Dijkstra(circuit_,x_depart,y_depart);



  vector<int> vitesses = (*dijkstra).DijkstraAlgo();

  std::ofstream myFile ("testcircuit.bin", std::ios::out | std::ios::binary);
  cout << "Valeurs de vitesses : ";
  for(int value : vitesses){
    myFile.write (reinterpret_cast<const char *>(&value), sizeof(value));
    cout << value << " , ";
  }
  cout << endl;
  myFile.close();


  (*dijkstra).~Dijkstra();


/*
  for(int i = 0; i < circuit_.size(); i++){

      for(int j = 0; j < circuit_[i].size(); j++){
        cout << circuit_[i][j];
      }
    cout << endl;
        }
*/


  //CheminALaMain();

  int lecture;

  std::ifstream myFileToRead ("chemin.bin", std::ios::out | std::ios::binary);
  myFileToRead.read (reinterpret_cast<char *>(&lecture), sizeof(lecture));
  std::cout << (int)lecture << ": lec " << std::endl;



  delete recupParam;



  return EXIT_SUCCESS;
}
