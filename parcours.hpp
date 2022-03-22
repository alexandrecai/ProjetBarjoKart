#ifndef PARCOURS_
#define PARCOURS_

using namespace std;


class Parcours{
    
    public: 
        Parcours();
        ~Parcours();
        
        bool positionValide(vector<vector<int> > _circuit, int x, int y);
        vector<pair<int,int> > getVoisins(vector<vector<int> > _circuit, int x, int y);
        void trouverFin(vector<vector<int> > _circuit, int x, int y);



};



#endif