#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>




using namespace std;

class Interface{
  private:
    map<string, pair<string,string> > listeCircuit;

  public:
    Interface();

    void initListeCircuit();
    vector<string> getInfosInterface();

    ~Interface();
};