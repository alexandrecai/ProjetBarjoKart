#ifndef RECUP_PARAM
#define RECUP_PARAM

#include <iostream>
#include "toml.hpp"
#include <vector>
#include <map>

class RecupParam{
  private:

    toml::table tbl;

    std::string nameParamFile;

    int accelerationMax;

    std::vector<int> rgbArrivee;

    std::map<std::string, int> coordonneesDepart;



  public:
    RecupParam();

    void setVarFromFile(std::string _paramFile);

    int getAccelerationMax();

    std::vector<int> getRgbArrivee();

    std::map<std::string, int> getCoordonneesDepart();

    ~RecupParam();

};

#endif
