#include<iostream>
#include<climits> // nécessaire pour INT_MAX
#include <vector>
#include <map>

class Dijkstra{
  private:

    // booleen permettant de savoir si on a trouvé un premier point d'arrivée
    bool PremiereArriveeTrouvee;

    // tableau à deux dimensions de int contenant le circuit
    std::vector<std::vector<int>> circuit;

    // coordonnée sur l'axe des abscisses du point de départ
    int x_depart;

    // coordonnée sur l'axe des ordonnées du point de départ
    int y_depart;

    // map contenant pour chaque point du circuit leur distance au point de départ
    std::map<std::pair<int,int>, int> mapDistance;

    // map contenant pour chaque point du ciruit le prédécesseur de ce point
    std::map<std::pair<int,int>, std::pair<int,int> > mapPredecessor;

    // pair contenant les coordonnées du point d'arrivée
    std::pair<int,int> arrivee;

    // liste contenant les points par lesquels passe le chemin pour aller du départ jusqu'à l'arrivée
    std::vector<std::pair<int,int>> listePoints;

  public:

    /**
     * constructeur
     * @param circuit   tableau à deux dimensions de int contenant le circuit à analyser
     * @param x_depart  coordonnée sur l'axe des abscisses du point de départ
     * @param y_depart  coordonnée sur l'axe des ordonnées du point de départ
     */
    Dijkstra(std::vector<std::vector<int>> circuit, int x_depart, int y_depart);

    /**
     * Fonction permettant de trouver un sommet de distance minimale du point de départ
     * @return un sommet de distance minimale du point de départ
     */
    std::pair<int,int> minDist();

    /**
     * Fonction retournant si tout les points du circuit ont été visités
     * @return si tout les points du circuit ont été visités
     */
    bool toutSommetsVisites();

    /**
     * Fonction qui permet d'initialiser l'algorithme de Dijkstra en
     * initialisant pour tout les points du circuit leur distance au point de départ à "+infini"
     * sauf le point de départ qui est initialisé à 0
     */
    void initDijkstra();

    /**
     * Fonction qui met à jour la distance minimale au point de départ
     * ainsi que le prédécesseur du point (i1, j1); en fonction de son voisin (i,j), le point visité.
     * @param i   coordonnée sur l'axe des abscisses du point visité
     * @param j   coordonnée sur l'axe des ordonnées du point visité
     * @param i1  coordonnée sur l'axe des abscisses du voisin
     * @param j1  coordonnée sur l'axe des ordonnées du voisin
     */
    void maj_distances( int i, int j, int i1, int j1);

    /**
     * Fonction principale de l'algorithme de Dijkstra
     * @return la liste des coordonnées du chemin que l'on prend
     */
    std::vector<int> DijkstraAlgo();

    /**
     * Fonction qui crée la pile des prédécesseurs du point d'arrivée jusqu'au point de départ
     * @return la liste des coordonnées du chemin que l'on prend
     */
    std::vector<int> chemin();

    /**
     * Permet de créer une image en noir et bleu
     * @param nomCircuit  nom du circuit à partir duquel on crée une image
     */
    void creationImage(std::string nomCircuit);

    /**
     * Fonction qui convertit la pile des prédécesseurs en liste de coordonnées
     * @param  listPoints la pile des prédécesseurs
     * @return la liste des coordonnées du chemin que l'on prend
     */
    std::vector<int> getVitessesDijkstra(std::vector<std::pair<int,int>> listPoints);

    /**
     * getter de la pile des prédécesseurs du point d'arrivée jusqu'au point de départ
     * @return la pile des prédécesseurs du point d'arrivée jusqu'au point de départ
     */
    std::vector<std::pair<int,int>> getListePoints();

    /**
     * Destructeur
     */
    ~Dijkstra();
};
