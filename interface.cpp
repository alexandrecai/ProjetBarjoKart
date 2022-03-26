#include "interface.hpp"

using namespace std;

Interface::Interface(){
  map<string, pair<string, string> > listeCircuit;
  initListeCircuit();
}

void Interface::initListeCircuit(){
  
  (*this).listeCircuit["tout_droit"] = make_pair("basique.png", "basique.toml");
  (*this).listeCircuit["ever_given"] = make_pair("ever_given.png", "ever_given.toml");
  (*this).listeCircuit["inter5tellar"] = make_pair("fusee.png", "fusee.toml");
  (*this).listeCircuit["prairie"] = make_pair("prairie.png", "prairie.toml");
  (*this).listeCircuit["mon_premier_circuit"] = make_pair("circuit0.png", "circuit1.toml");
  (*this).listeCircuit["dilemne_dilenme"] = make_pair("surprise.png", "surprise.toml");
  (*this).listeCircuit["pi"] = make_pair("trois_quatorze.png", "trois_quatorze.toml");
  (*this).listeCircuit["athens"] = make_pair("bcnr.png", "bcnr.toml");
  (*this).listeCircuit["ballade_amnesique"] = make_pair("mulholland_drive.png", "mulholland_drive.toml");
  (*this).listeCircuit["very_fast_food"] = make_pair("fast_food.png", "fast_food.toml");
  (*this).listeCircuit["adaptallure"] = make_pair("adaptallure.png", "adaptallure.toml");
}

vector<string> Interface::getInfosInterface(){
  string toml;
  string png;
  string nom;
  string bin;
  vector<string> valeurs;

  cout << "Veuillez choisir un circuit parmis : " << endl;
  for(const auto& circuit : (*this).listeCircuit){
    cout << " -> " <<  circuit.first << endl;
  }
  cin >> nom ;
  cout << "Veuillez choisir le nom du fichier .bin en sorti : " << endl;
  cin >> bin ;
  
  png = (*this).listeCircuit[nom].first;
  toml = (*this).listeCircuit[nom].second;

  bin = bin + ".bin";

  valeurs.push_back(png);
  valeurs.push_back(toml);
  valeurs.push_back(bin);

  return valeurs;
}

// destructeur
Interface::~Interface(){
  cout<<"Destruction de Interface" <<endl;
}