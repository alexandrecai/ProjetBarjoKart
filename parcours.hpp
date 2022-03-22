#ifndef PARCOURS_HPP
#define PARCOURS_HPP


using namespace std;

class parcours
{
    private:
    
    public:
        parcours();
        ~parcours();

        void trouverFin(vector<vector<int> > _circuit, int x, int y);
        bool positionValide(vector<vector<int> > _circuit, int x, int y);
        vector<pair<int,int> > getVoisins(vector<vector<int> > _circuit, int x, int y);

};






#endif