#ifndef PARCOURS_
#define PARCOURS_

#include <png++/png.hpp>

using namespace std;

class Parcours{
    private:


    public:


        Parcours();
        ~Parcours();
        void trouverFin(vector<vector<int> > _circuit, int x, int y);
        vector<pair<int,int> > getVoisins(vector<vector<int> > _circuit, int x, int y);
        bool positionValide(vector<vector<int> > _circuit, int x, int y);



};

#endif