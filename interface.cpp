#include "interface.hpp"

using namespace std;

Interface::Interface(){
  map<string, pair<string, string> > listeCircuit;
  initListeCircuit();
}

void Interface::initListeCircuit(){

  (*this).listeCircuit["tout droit"] = make_pair("basique.png", "basique.toml");
  (*this).listeCircuit["ever given"] = make_pair("ever_given.png", "ever_given.toml");
  (*this).listeCircuit["inter5tellar"] = make_pair("fusee.png", "fusee.toml");
  (*this).listeCircuit["prairie"] = make_pair("prairie.png", "prairie.toml");
  (*this).listeCircuit["mon premier circuit"] = make_pair("circuit0.png", "circuit1.toml");
  (*this).listeCircuit["dilemne dilenme"] = make_pair("surprise.png", "surprise.toml");
  (*this).listeCircuit["pi"] = make_pair("trois_quatorze.png", "trois_quatorze.toml");
  (*this).listeCircuit["athens"] = make_pair("bcnr.png", "bcnr.toml");
  (*this).listeCircuit["ballade amnesique"] = make_pair("mulholland_drive.png", "mulholland_drive.toml");
  (*this).listeCircuit["very fast food"] = make_pair("fast_food.png", "fast_food.toml");
  (*this).listeCircuit["adaptallure"] = make_pair("adaptallure.png", "adaptallure.toml");
}

vector<string> Interface::getInfosInterface(){
  string toml;
  string png;
  string nom;
  string bin;
  vector<string> valeurs;

  bool isCircuitExist = false;


  cout << R"(

██████╗  █████╗ ██████╗      ██╗ ██████╗ ██╗  ██╗ █████╗ ██████╗ ████████╗    ██████╗ ██████╗
██╔══██╗██╔══██╗██╔══██╗     ██║██╔═══██╗██║ ██╔╝██╔══██╗██╔══██╗╚══██╔══╝    ╚════██╗╚════██╗
██████╔╝███████║██████╔╝     ██║██║   ██║█████╔╝ ███████║██████╔╝   ██║        █████╔╝ █████╔╝
██╔══██╗██╔══██║██╔══██╗██   ██║██║   ██║██╔═██╗ ██╔══██║██╔══██╗   ██║       ██╔═══╝  ╚═══██╗
██████╔╝██║  ██║██║  ██║╚█████╔╝╚██████╔╝██║  ██╗██║  ██║██║  ██║   ██║       ███████╗██████╔╝
╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚═════╝

)" << "\n" << endl;


  while (!isCircuitExist) {

    cout << "Veuillez choisir un circuit parmi : " << endl;

    for(const auto& circuit : (*this).listeCircuit){
      cout << " -> " <<  circuit.first << endl;
    }

    cout << "\n -> custom (vous choisissez une map n'étant pas présente dans la liste ci-dessus)\n" << endl;

    getline(cin, nom);
    cout << "\nVous avez choisi le circuit : " << nom << endl;


    // si ce circuit existe dans notre map "listeCircuit"
    if((*this).listeCircuit.count(nom)){
      // si les fichiers de configuration (.png et .toml) du circuit sont présents
      if(filesystem::exists((*this).listeCircuit[nom].first) && filesystem::exists((*this).listeCircuit[nom].second)){
        isCircuitExist = true;
        png = (*this).listeCircuit[nom].first;
        toml = (*this).listeCircuit[nom].second;
      }
      else
        cout << "\nVeuillez télécharger les fichiers .png et .toml correspondants au circuit.\n" << endl;
    }

    // si vous avez choisi la map custom
    else if (nom=="custom"){
      cout << "\nVeuillez choisir un fichier de configuration .toml pour votre circuit.\n" << endl;
      getline(cin, toml);
      cout <<"\nVous avez choisi le fichier " << toml << "\n" << endl;

      cout << "\nVeuillez choisir une image .png pour votre circuit.\n" << endl;
      getline(cin, png);
      cout <<"\nVous avez choisi le fichier " << png << "\n" << endl;

      if(filesystem::exists(toml) && filesystem::exists(png))
        isCircuitExist = true;
      else
        cout <<"\nLes fichiers choisis ne sont pas dans le répertoire courant. Veuillez réessayer.\n" << endl;
    }


    else
      cout << "\nCe circuit n'existe pas. Veuillez réessayer.\n" << endl;

  }


  cout << "\nVeuillez choisir le nom du fichier .bin en sortie \n" << endl;
  getline(cin, bin);
  cout << "\nVous avez choisi comme nom pour votre fichier binaire : " << bin << endl;



  bin = bin + ".bin";

  cout << "\nLe calcul de la trajectoire optimale est en cours. Veuillez patienter... \n\n" << endl;

  valeurs.push_back(png);
  valeurs.push_back(toml);
  valeurs.push_back(bin);

  return valeurs;
}


void Interface::affichageScore(int nbEtapes, string bin){
  int score = 10000 - nbEtapes;

  cout << "\nLe fichier binaire «" << bin << "» contenant la trajectoire a bien été créé." << endl;

  cout << "\nVous avez obtenu un score de " << score << " points sur ce circuit. Félicitations !\n" << endl;
}

// destructeur
Interface::~Interface(){
  cout<<"Destruction de Interface" <<endl;
}
