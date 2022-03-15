#ifndef CIRCUIT_
#define CIRCUIT_


#include <png++/png.hpp>

using namespace std;

class Circuit{
    private:

        //Image du circuit
        png::image< png::rgb_pixel > imageCircuit;

        int width;
        int height;

        //Tableau de string qui contient la carte du circuit
        std::vector<std::vector<std::string> > carte;

    public:

        Circuit(string _circuit);

       
        string getCarte();

        //Recuperation case a proximite
        void getCasesProxim(int x, int y);


        



};

#endif