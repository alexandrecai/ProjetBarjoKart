#include "circuit.hpp"

using namespace png;
using namespace std;

// constructeur
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

// destructeur
Circuit::~Circuit(){
    //std::cout << "Destruction du Circuit" << std::endl;
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
    for(size_t i = 0; i < image.get_height(); i++){
        vector<int> ligne;
        for(size_t j = 0; j < image.get_width(); j++){
            png::rgb_pixel pixel = image[i][j];

            // Si le pixel est rouge, c'est l'arrivée
            if (pixel.red == couleur_arrivee.red && (int) pixel.blue < 160 && (int) pixel.green < 160){
                ligne.push_back(9);
            }
            // Si le pixel est blanc, c'est la piste
            else if (pixel.red == 255 && pixel.blue == 255 && pixel.green == 255){
                ligne.push_back(0);
            }
            // Si le est noir, c'est un mur
            else if (pixel.red == 0 && pixel.blue == 0 && pixel.green == 0){
                ligne.push_back(2);
            }
            // On initialise le pixel de départ à 0
            else if (i == (size_t) _x_depart && j == (size_t)  _y_depart){
                ligne.push_back(0);
            }
            // On met tous les autres pixels à 2
            else {
                ligne.push_back(2);
            }



        }
        circuit.push_back(ligne);
    }
    return circuit;
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


vector<vector<int> > Circuit::ajoutChemin(vector<vector<int> > circuitFinal ,vector<int> pointsPassage, int x_depart, int y_depart, int acc_max){

    int pos_x = x_depart;
    int pos_y = y_depart;

    int vitesse_x = 0;
    int vitesse_y = 0;

    int nouvelle_vitesse_x = 0;
    int nouvelle_vitesse_y = 0;

    int accelTotale = 0;

    vector<vector<int> > pointsAAjouter;
    vector<int> pointSuivant;

    cout << "acc_max : " << acc_max << endl;

    //Ajout des positions des points où l'on passe à la liste pointsAAjouter
    for(size_t placeValeurAccel = 0; placeValeurAccel < pointsPassage.size() ; placeValeurAccel = placeValeurAccel + 2){

        nouvelle_vitesse_x = pointsPassage[placeValeurAccel];
        nouvelle_vitesse_y = pointsPassage[placeValeurAccel+1];

        cout << "----------------------------------" << endl;
        cout << "new x" << nouvelle_vitesse_x << endl;
        cout << "new y" << nouvelle_vitesse_y << endl;
        cout << "----------------------------------" << endl;


        accelTotale = abs(nouvelle_vitesse_x - vitesse_x);
        accelTotale = accelTotale + abs(nouvelle_vitesse_y - vitesse_y);

        cout << "----------------------------------" << endl;
        cout << "x" << abs(nouvelle_vitesse_x - vitesse_x) << endl;
        cout << "y" << abs(nouvelle_vitesse_y - vitesse_y) << endl;
        cout << "----------------------------------" << endl;

        cout << "----------------------------------" << endl;
        cout << accelTotale << endl;
        cout << "----------------------------------" << endl;

        if(accelTotale > acc_max){

            cout << "Tete a queue" << endl;

            break;
        }

        else{

            vitesse_x = nouvelle_vitesse_x;
            vitesse_y = nouvelle_vitesse_y;

            pos_x = pos_x + vitesse_x;
            pos_y = pos_y + vitesse_y;

            pointSuivant.push_back(pos_x);
            pointSuivant.push_back(pos_y);

            pointsAAjouter.push_back(pointSuivant);

            pointSuivant.clear();

        }

    }

    for(vector<int> pointActuel : pointsAAjouter){
        for(size_t hauteur = 0; hauteur < circuitFinal.size(); hauteur++){
            for(size_t largeur = 0; largeur < circuitFinal[hauteur].size(); largeur++){
                if(hauteur == (size_t) x_depart && largeur == (size_t) y_depart){
                    circuitFinal[hauteur][largeur] = 1;
                }
                if(hauteur == (size_t) pointActuel[0] && largeur == (size_t) pointActuel[1] && circuitFinal[hauteur][largeur] == 9){
                    cout << "Vous avez réussi !" << endl;
                    circuitFinal[hauteur][largeur] = 7;
                }
                if(hauteur == (size_t)  pointActuel[0] && largeur == (size_t)  pointActuel[1] && circuitFinal[hauteur][largeur] == 1){
                    cout << "Tete a queue" << endl;
                    break;
                }
                if(hauteur == (size_t)  pointActuel[0] && largeur == (size_t)  pointActuel[1] && circuitFinal[hauteur][largeur] != 7){
                    circuitFinal[hauteur][largeur] = 1;
                }
                if(pointActuel[0] < 0 || (size_t) pointActuel[1] < 0 || (size_t) pointActuel[0] > circuitFinal.size()-1 || (size_t) pointActuel[1] >circuitFinal.size()-1){
                    cout << "Sortie de piste" << endl;
                    return circuitFinal;

                }

            }
        }
    }

    return circuitFinal;
}


vector<vector<int> > Circuit::bresenham(vector<vector<int> > circuitFinal,int x1, int y1, int x2, int y2)
{

   if(x2-x1 >= y2-y1){
        int pente = 2 * (y2 - y1);
        int rectification_pente = pente - (x2 - x1);
        for (int x = x1, y = y1; x < x2; x++){
            cout << "(" << x << "," << y << ")\n";

            circuitFinal[x][y] = 1;

            rectification_pente += pente;


            if (rectification_pente >= 0){
                y++;
                rectification_pente  -= 2 * (x2 - x1);
            }
        }
   }
   else{
        int pente = 2 * (x2 - x1);
        int rectification_pente = pente - (y2 - y1);
        for (int x = x1, y = y1; y < y2; y++){
            cout << "(" << x << "," << y << ")\n";

            circuitFinal[x][y] = 1;


            rectification_pente += pente;

            if (rectification_pente >= 0){
                x++;
                rectification_pente  -= 2 * (y2 - y1);
            }
        }
   }

   return circuitFinal;
}
