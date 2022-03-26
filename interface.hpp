#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <filesystem>




using namespace std;

class Interface{
  private:
    map<string, pair<string,string> > listeCircuit;

  public:
    Interface();

    void initListeCircuit();

    vector<string> getInfosInterface();

    void affichageScore(int nbEtapes, string bin);

    ~Interface();
};
