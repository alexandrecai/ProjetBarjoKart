#include "circuit.hpp"

using namespace png;

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

    /*
    for (int i = 0; i < (*this).width; i++){
        for (int j = 0; j < (*this).image.get_height(); j++){
            png::rgb_pixel pixel = image[j][i];
            if (pixel.red == 255 && pixel.blue == 255 && pixel.green == 255){
                (*this).carte[i][j] = "O";
            }
            else if (pixel.red == 255 && pixel.blue == 0 && pixel.green == 0){
                (*this).carte[i][j] = "A";
            }
            else if (pixel.red == 0 && pixel.blue == 0 && pixel.green == 255){
                (*this).carte[i][j] = "D";
            }
            else {
                (*this).carte[i][j] = "X";
            }
        }
    }*/


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
