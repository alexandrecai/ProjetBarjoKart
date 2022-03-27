#ifndef PARCOURS_
#define PARCOURS_

#include <png++/png.hpp>

using namespace std;

class Parcours{
    private:


    public:

        /**
         * Constructeur
         */
        Parcours();


        /**
         * Destructeur
         */
        ~Parcours();


        /**
         * Implémentation du parcours en profondeur
         * @param _circuit  tableau à deux dimensions de int contenant le circuit
         * @param x         coordonnée sur l'axe des abscisses du point de départ
         * @param y         coordonnée sur l'axe des ordonnées du point de départ
         */
        void trouverFin(vector<vector<int>> _circuit, int x, int y);


        /**
         * Foncttion qui récupère les voisins d'un point(x,y)
         * @param _circuit  tableau à deux dimensions de int contenant le circuit
         * @param x         coordonnée sur l'axe des abscisses du point dont on cherche les voisins
         * @param y         coordonnée sur l'axe des ordonnées du point dont on cherche les voisins
         * @return la liste des voisins du point(x,y)
         */
        vector<pair<int,int>> getVoisins(vector<vector<int>> _circuit, int x, int y);


        /**
         * Fonction qui vérifie le psitionnement du point(x,y)
         * @param _circuit  tableau à deux dimensions de int contenant le circuit
         * @param x         coordonnée sur l'axe des abscisses du point sur lequel on se situe
         * @param y         coordonnée sur l'axe des ordonnées du point sur lequel on se situe
         * @return          si le psitionnement du point(x,y) est valide
         */
        bool positionValide(vector<vector<int> > _circuit, int x, int y);


        /**
         * Algorithme de test permettant de parcourir le circuit "c'est tout droit". 
         */
        void CheminAlaMain();



};

#endif
