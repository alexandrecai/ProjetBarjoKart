#include "dijkstra.hpp"
#include <png++/png.hpp>

using namespace std;
using namespace png;

// constructeur
Dijkstra::Dijkstra(vector<vector<int> > _circuit, int _x_depart, int _y_depart){
  (*this).circuit = _circuit;
  (*this).x_depart = _y_depart;
  (*this).y_depart = _x_depart;
  (*this).PremiereArriveeTrouvee = false;
}


pair<int, int> Dijkstra::minDist()
{

    int minimum=INT_MAX;

    pair<int, int> indexSommet;

    for(int i = 0; i < (int) (*this).circuit.size(); i++){
      for(int j = 0; j < (int) (*this).circuit[i].size(); j++){
        if(circuit[i][j]==0 && mapDistance.at(make_pair(i,j)) <= minimum){

          minimum = mapDistance.at(make_pair(i,j));
          indexSommet = make_pair(i,j);

        }
      }
    }
    return indexSommet;
}



bool Dijkstra::toutSommetsVisites(){

  for(int i = 0; i < (int) (*this).circuit.size(); i++){
    for(int j = 0; j < (int) (*this).circuit[i].size(); j++){
      if(!(circuit[i][j]==2)){
        if(circuit[i][j]==0){
          return false;
        }
      }
    }
  }

  return true;
}


void Dijkstra::initDijkstra(){
  int nombrePointsMapDistance = 0; //Nombre de pixels à parcourir
  int nombreTotal = 0; //Nombre de pixels total sur l'image
  for(int i = 0; i < (int) (*this).circuit.size(); i++){
    for(int j = 0; j < (int) (*this).circuit[i].size(); j++){
      if(!(circuit[i][j]==2)){
        (*this).mapDistance[make_pair(i,j)]=INT_MAX;
        nombrePointsMapDistance++;
      }

      nombreTotal++;
    }
  }
  mapDistance[make_pair((*this).x_depart,(*this).y_depart)]=0;
}



void Dijkstra::maj_distances(int i, int j, int i1, int j1){

  bool voisin = false;
  if(i1==i+1 && j1==j && i != ((int)(*this).circuit.size() - 1)){
    voisin = true;
  }
  if(i1 == i-1 && j1==j && i!=0){
    voisin = true;
  }
  if(j1==j+1 && i1==i && j != ((int)(*this).circuit[i].size() - 1)){
    voisin = true;
  }
  if(j1 == j-1 && i1==i && j!=0){
    voisin = true;
  }



  /*
  liste des conditions :
    - si point(i1,j1) est voisin de point(i,j)
    - si point(i1,j1) n'est pas un mur
    - si point(i1,j1) est un point non visité ou un point de l'arrivée
    - s'il existe un chemin connu depuis point(i,j) jusqu'au départ
    - si point(i1,j1) n'a pas été visité ou que chemin(de départ à point(i1,j1)) passe par un plus long chemin
  */
  if(voisin && circuit[i1][j1] != 2) {
    if( ((*this).circuit[i1][j1]==0 || (*this).circuit[i1][j1]==9) && (*this).mapDistance.at(make_pair(i,j))!=INT_MAX &&
                                                    (*this).mapDistance.at(make_pair(i,j))+1<(*this).mapDistance.at(make_pair(i1,j1)) ){

      (*this).mapDistance[make_pair(i1,j1)]=(*this).mapDistance[make_pair(i,j)]+1; //Ajout de 1 à la distance

      (*this).mapPredecessor[make_pair(i1,j1)]=make_pair(i,j); //Ajout du prédécesseur


      // on set l'arrivée
      if((*this).circuit[i1][j1]==9 && !PremiereArriveeTrouvee){

        (*this).arrivee=make_pair(i1,j1);
        PremiereArriveeTrouvee=true;
      }
    }
  }
}


vector<int> Dijkstra::DijkstraAlgo(){

  int compteurMinDist = 0;

  initDijkstra();

  int numberIteration=0;  //Nombre de pixels visités avant d'arriver à la fin
  while (!PremiereArriveeTrouvee) {


    pair<int,int> m = (*this).minDist(); // pixel m

    compteurMinDist++;
    (*this).circuit[m.first][m.second] = 1;

    for(int i = m.first - 1; i <= m.first+1; i++ ){
      for(int j = m.second - 1; j <= m.second+1; j++ ){
        if(i >=0 && j >=0 && i < (int)(*this).circuit.size() && j < (int)(*this).circuit[m.first].size()){
          numberIteration++;
          maj_distances(m.first, m.second, i, j);
        }
      }
    }

  }
  vector<int> vitesses = chemin();
  return vitesses;
}


vector<int> Dijkstra::chemin(){

  map<pair<int,int>,pair<int,int> > pred = (*this).mapPredecessor; // map des predecesseurs
  vector<pair<int,int> > listPoints; // liste de tt les points du chemin

  pair<int,int> Sdeb = make_pair((*this).x_depart,(*this).y_depart); // point de depart
  pair<int,int> currentSommet = (*this).arrivee;

  bool isValid = true;
  while(isValid){
    listPoints.insert(listPoints.begin(), currentSommet);
    currentSommet = mapPredecessor[make_pair(currentSommet.first, currentSommet.second)];
    if(currentSommet.first == Sdeb.first && currentSommet.second == Sdeb.second)
      isValid = false;
  }

  listPoints.insert(listPoints.begin(), Sdeb);

  // Affichage du chemin


  (*this).listePoints = listPoints;

  return getVitessesDijkstra(listPoints);

}

//Creation d'une image de tous les points sur lesquels on est passé
void Dijkstra::creationImage(string nomCircuit){
  png::image< png::rgb_pixel > image(nomCircuit);
  for(size_t i =0; i < (*this).circuit.size(); i++){
    for(size_t j = 0; j < (*this).circuit[i].size(); j++){
      if ((*this).circuit[i][j] == 1){
        image.set_pixel(j,i,png::rgb_pixel(0,0,255));
      }
      else{
        image.set_pixel(j,i,png::rgb_pixel(0,0,0));
      }

    }

  }
  image.write("visited_" + nomCircuit);
}


vector<int> Dijkstra::getVitessesDijkstra(vector<pair<int,int> > listPoints){
  vector<int> vitesses;

  int v_x = 0;
  int v_y = 0;

  int dif_x = 0;
  int dif_y = 0;

  int x_prec = INT_MAX;
  int y_prec = INT_MAX;

  for(pair<int,int> point : listPoints){

    if(x_prec != INT_MAX && y_prec != INT_MAX){
      dif_x = point.first - x_prec;
      dif_y = point.second - y_prec;


    }
    else{
      dif_x = point.first - x_depart;
      dif_y = point.second - y_depart;
    }



    v_x = dif_x;
    v_y = dif_y;


    vitesses.push_back(v_y);
    vitesses.push_back(v_x);


    x_prec = point.first;
    y_prec = point.second;
  }



  return vitesses;
}

vector<pair<int,int>> Dijkstra::getListePoints(){
  return (*this).listePoints;
}


// destructeur
Dijkstra::~Dijkstra(){
  //cout<<"Destruction de Dijkstra" <<endl;
}
