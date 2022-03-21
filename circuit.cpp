#include "circuit.hpp"

using namespace png;

//Nettoyer le fichier (modifier le constructeur)

Circuit::Circuit(std::string _circuit){
    png::image< png::rgb_pixel > image(_circuit);
    (*this).imageCircuit = image;
    (*this).width = imageCircuit.get_width();
    (*this).height = imageCircuit.get_height();



    for (int i = 0; i < (*this).height; i++){
        std::vector<std::string> ligne;
        for (int j = 0; j < (*this).width; j++){
            png::rgb_pixel pixel;
            pixel = imageCircuit[i][j];
            if (pixel.red == 255 && pixel.blue == 255 && pixel.green == 255){
                ligne.push_back("-");
            }
            else if (pixel.red == 255 && pixel.blue == 0 && pixel.green == 0){
                ligne.push_back("A");
            }
            else if (pixel.red == 0 && pixel.blue == 0 && pixel.green == 255){
                ligne.push_back("D");
            }
            else {
                ligne.push_back("X");
            }
        }
        (*this).carte.push_back(ligne);
    }
 
}

 
// Creation d'un tableau a 2 dimensions representant le circuit
// 9 = arrivee
// 0 = piste
// 2 == mur
vector<vector<int> > Circuit::generateCircuit(string _imageCircuit, std::vector<int> _couleur_arrivee, int _x_depart, int _y_depart){
    png::image< png::rgb_pixel > image(_imageCircuit);

    png::rgb_pixel couleur_arrivee;
    couleur_arrivee.red = _couleur_arrivee[0]; 
    couleur_arrivee.green = _couleur_arrivee[1];
    couleur_arrivee.blue = _couleur_arrivee[2];

    vector<vector<int> > circuit;

    for(int i = 0; i < image.get_height(); i++){
        vector<int> ligne;
        for(int j = 0; j < image.get_width(); j++){
            png::rgb_pixel pixel = image[i][j];
            if (pixel.red == couleur_arrivee.red && pixel.blue == couleur_arrivee.blue && pixel.green == couleur_arrivee.green){
                ligne.push_back(9);
            }
            else if (pixel.red == 255 && pixel.blue == 255 && pixel.green == 255){
                ligne.push_back(0);
            }
            else if (pixel.red == 0 && pixel.blue == 0 && pixel.green == 0){
                ligne.push_back(2);
            }
            else if (i == _x_depart && j == _y_depart){
                ligne.push_back(0);
            }
            
        

        }
        circuit.push_back(ligne);
    }


}



}

string Circuit::getCarte(){
    string carte = "";
    for (int i = 0; i < (int) (*this).carte.size(); i++){
        for (int j = 0; j < (int) (*this).carte[i].size(); j++){
            carte += (*this).carte[i][j];
            cout << (*this).carte[i][j];
        }
        cout << endl;
        carte += "\n";
    }
    return carte;
}

void Circuit::getCasesProxim(int x, int y){
    cout << "(" << x << ", " << y << ")" << endl;
}
