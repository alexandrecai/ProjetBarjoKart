#ifndef RECUP_PARAM
#define RECUP_PARAM

#include <iostream>
#include "toml.hpp"
#include <vector>
#include <map>

class RecupParam{
  private:

    // table Toml
    toml::table tbl;

    // string contenant le nom du fichier de paramètres (ex: "circuit1.toml")
    std::string nameParamFile;

    // accélération maximale
    int accelerationMax;

    // tableau contenant les valeurs RGB du point d'arrivée
    std::vector<int> rgbArrivee;

    // map contenant les coordonnées du point de départ sur les axes des abscisses et des ordonnées
    std::map<std::string, int> coordonneesDepart;



  public:
    /**
     * Constructeur
     */
    RecupParam();

    /**
     * Méthode principale. Récupère les différents paramètres issus du fichier .toml
     * @param _paramFile  le nom du fichier de paramètres
     */
    void setVarFromFile(std::string _paramFile);

    /**
     * getter de l'accélération maximale
     * @return l'accélération maximale
     */
    int getAccelerationMax();

    /**
     * getter des valeurs RGB du point d'arrivée
     * @return les valeurs RGB du point d'arrivée
     */
    std::vector<int> getRgbArrivee();

    /**
     * getter des coordonnées du point de départ
     * @return les coordonnées du point de départ
     */
    std::map<std::string, int> getCoordonneesDepart();

    /**
     * Destructeur
     */
    ~RecupParam();

};

#endif
