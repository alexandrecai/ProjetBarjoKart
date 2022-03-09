#include "recupParam.hpp"

int main(int argc, char const *argv[]) {

  // Tests montrants le fonctionnement de la classe permettant de récupérer les paramètres issus du .toml .

  RecupParam *recupParam = new RecupParam();

  // méthode obligatoire - permet "lire" le .toml et d'en extraire les paramètres
  (*recupParam).setVarFromFile();

  //getters
  int acc_max = (*recupParam).getAccelerationMax();

  std::vector<int> couleur_arrivee = (*recupParam).getRgbArrivee();

  std::map<std::string, int> depart = (*recupParam).getCoordonneesDepart();

  std::cout << std::endl;

  delete recupParam;

  return EXIT_SUCCESS;
}
