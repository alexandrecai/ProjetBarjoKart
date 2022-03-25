#include<iostream>
#include<climits> // nécessaire pour INT_MAX
#include <vector>
#include <map>

class Dijkstra{
  private:
    int distance[6];
    bool Tset[6];

    std::vector<std::vector<int> > circuit;

    int x_depart;
    int y_depart;

    std::map<std::pair<int,int>, int> mapDistance;

    std::map<std::pair<int,int>, std::pair<int,int> > mapPredecessor;

    std::pair<int,int> arrivee;

  public:

    Dijkstra(std::vector<std::vector<int> >, int, int);

    std::pair<int,int> minDist();

    bool toutSommetsVisites();

    void initDijkstra();

    void maj_distances( int i, int j, int i1, int j1);

    void DijkstraAlgo();

    void chemin();

    ~Dijkstra();
};
