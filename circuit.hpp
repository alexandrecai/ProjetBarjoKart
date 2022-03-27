#ifndef CIRCUIT_
#define CIRCUIT_


#include <png++/png.hpp>

using namespace std;

class Circuit{
    private:

        // Image du circuit
        png::image< png::rgb_pixel > imageCircuit;

        // Largeur du circuit
        int width;

        // Hauteur du circuit
        int height;

        // Tableau de string qui contient la carte du circuit
        vector<vector<string>> carte;

    public:

        /**
         * Constructeur
         * @param _circuit : nom du circuit
         */
        Circuit(string _circuit);


        /**
         * Destructeur
         */
        ~Circuit();


        /**
         * getter de la carte
         * @return un string de la carte
         */
        string getCarte();


        /**
         * On génère un circuit sous la forme d'un tableau à 2 dimensions de int
         * @param image            nom de l'image (.png)
         * @param couleur_arrivee  tableau contenant les valeurs RGB de l'arrivée
         * @param x_depart         int contenant la coordonnée sur l'axe des abscisses du point de départ
         * @param y_depart         int contenant la coordonnée sur l'axe des ordonnées du point de départ
         * @return un tableau à 2 dimensions de int contenant le circuit généré
         */
        vector<vector<int> > generateCircuit(string image, vector<int> couleur_arrivee, int x_depart, int y_depart);


        /**
         * Recuperation case a proximite
         * @param x  coordonnée sur l'axe des abscisses
         * @param y  coordonnée sur l'axe des ordonnées
         */
        void getCasesProxim(int x, int y);


        /**
         * On génère un circuit sous la forme d'un tableau à 2 dimensions de int muni du chemin que l'on emprunte
         * @param circuitFinal   circuit généré précédemment
         * @param pointsPassage  liste des points de passage de notre chemin
         * @param x_depart       int contenant la coordonnée sur l'axe des abscisses du point de départ
         * @param y_depart       int contenant la coordonnée sur l'axe des ordonnées du point de départ
         * @param acc_max        accélération maximale autorisée sur le circuit
         * @return tableau à 2 dimensions de int muni du chemin que l'on emprunte
         */
        vector<vector<int> > ajoutChemin(vector<vector<int> > circuitFinal, vector<int> pointsPassage, int x_depart, int y_depart, int acc_max);


        /**
         * Implémentation de l'algorithme de Bresenham
         * @param circuitFinal  circuit muni du chemin que l'on emprunte
         * @param x1            coordonnée sur l'axe des abscisses du point de départ
         * @param y1            coordonnée sur l'axe des ordonnées du point de départ
         * @param x2            coordonnée sur l'axe des abscisses du point d'arrivée
         * @param y2            coordonnée sur l'axe des ordonnées du point d'arrivée
         * @return circuit optimisé par l'algorithme
         */
        vector<vector<int>> bresenham(vector<vector<int> > circuitFinal,int x1, int y1, int x2, int y2);



};

#endif
