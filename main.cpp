#include "recupParam.hpp"
#include "circuit.hpp"

using namespace std;

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


  delete recupParam;

  return EXIT_SUCCESS;
}
