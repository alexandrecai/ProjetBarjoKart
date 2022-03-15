#include "recupParam.hpp"

using namespace std;

// constructeur
RecupParam::RecupParam(){}


void RecupParam::setVarFromFile(string paramFile){
  //std::cout << "Donnez le nom d'un fichier de paramètre (ex: param.toml) : " << '\n'<< std::endl;
  //std::cin >> (*this).nameParamFile;
  //std::cout << "Nom des paramètres enregistré" << '\n';
  (*this).nameParamFile = paramFile;
  try
  {
      (*this).tbl = toml::parse_file((*this).nameParamFile);
      std::cout << (*this).tbl << "\n";

      std::cout << "\n" << "~~~~~~~~~~~~" << '\n' << std::endl;

      // récup accel max

      (*this).accelerationMax = (*this).tbl.get("acc_max")->value<int>().value();
      std::cout << "accelerationMax : " << (*this).accelerationMax << '\n';


      // récup rgb
      std::cout << "rgb : [";

      for(int i = 0; i <= 2; i++){
         (*this).rgbArrivee.push_back( (*this).tbl["couleur_arrivee"].as_array()[0].at(i).value<int>().value() );
         std::cout << (*this).rgbArrivee[i];
         if(i!=2){
           std::cout << ", ";
         }
      }

      std::cout << "]" << std::endl;


      // recup coordonnées départ

      (*this).coordonneesDepart["x"] = (*this).tbl["depart"]["x"].value<int>().value();
      (*this).coordonneesDepart["y"] = (*this).tbl["depart"]["y"].value<int>().value();

      std::cout << (*this).coordonneesDepart["x"] << '\n';

      std::cout << (*this).coordonneesDepart["y"] << '\n';

  }
  catch (const toml::parse_error& err)
  {
      std::cerr << "Parsing failed:\n" << err << "\n";
  }
}


int RecupParam::getAccelerationMax(){
  return (*this).accelerationMax;
}


std::vector<int> RecupParam::getRgbArrivee(){
  return (*this).rgbArrivee;
}


std::map<std::string, int> RecupParam::getCoordonneesDepart(){
  return (*this).coordonneesDepart;
}


RecupParam::~RecupParam(){
  cout << "Destruction de RecupParam" << endl;
}
