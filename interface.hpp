#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <filesystem>




using namespace std;

class Interface{
  private:

    // la liste des circuits disponibles sur barjokart.site
    map<string, pair<string,string> > listeCircuit;

  public:

    /**
     * Constructeur
     */
    Interface();

    /**
     * Méthode qui initialise la map contenant les circuits
     */
    void initListeCircuit();

    /**
     * Interface "menu", récupère les choix de map et de noms de fichiers de sortie du joueur
     * @return sous la forme d'une liste -> les choix de map et de noms de fichiers de sortie du joueur
     */
    vector<string> getInfosInterface();

    /**
     * Méthode permettant d'afficher le score obtenu sur un circuit donnée.
     * Affiche également que le fichier binaire a bien été créé.
     * @param nbEtapes  nombre d'étapes nécessaires pour par courir le circuit
     * @param bin       nom du fichier binaire de sortie, choisi par l'utilisateur
     */
    void affichageScore(int nbEtapes, string bin);

    /**
     * Destructeur
     */
    ~Interface();
};
