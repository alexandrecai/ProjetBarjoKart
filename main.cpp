#include "recupParam.hpp"
#include "circuit.hpp"
#include "parcours.hpp"
#include "dijkstra.hpp"
#include "interface.hpp"
#include <fstream>
#include <stdlib.h>

using namespace std;


int main() {

  Interface *interface = new Interface();
  vector<string> choixCircuit = (*interface).getInfosInterface();

  // Tests montrants le fonctionnement de la classe permettant de récupérer les paramètres issus du .toml .

  //Parametres de configuration
  string paramFile = choixCircuit[1];
  string circuit = choixCircuit[0];


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


	Dijkstra *dijkstra = new Dijkstra(circuit_,x_depart,y_depart);



  vector<int> vitesses = (*dijkstra).DijkstraAlgo();
  (*dijkstra).creationImage(choixCircuit[0]);

  std::ofstream myFile (choixCircuit[2], std::ios::out | std::ios::binary);
  cout << "Valeurs de vitesses : ";
  for(int value : vitesses){
    myFile.write (reinterpret_cast<const char *>(&value), sizeof(value));
    cout << value << " , ";
  }
  cout << endl;
  myFile.close();



  int lecture;

  std::ifstream myFileToRead ("chemin.bin", std::ios::out | std::ios::binary);
  myFileToRead.read (reinterpret_cast<char *>(&lecture), sizeof(lecture));
  std::cout << (int)lecture << ": lec " << std::endl;

  (*interface).affichageScore((int)(*dijkstra).getListePoints().size(), choixCircuit[2]);

  delete dijkstra;

  delete recupParam;
  delete circuitTest;
  delete interface;


  return EXIT_SUCCESS;
}
