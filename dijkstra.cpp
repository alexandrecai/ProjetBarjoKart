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


pair<int, int> Dijkstra::minDist() // finding minimum distance
{
  //new version

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
    /*
    liste des conditions :
      - si k n'a pas été visité -> !Tset[k]
      - si k est voisin de m -> graph[m][k]
      - s'il existe un chemin depuis m jusqu'à Sdeb -> distance[m]!=INT_MAX
      - si k n'a pas été visité ou que chemin(de Sdeb à k) passe par un plus long chemin-> distance[m]+graph[m][k]<distance[k]
  */

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



  if(voisin && circuit[i1][j1] != 2) {
 
    //cout<<"----------------"<<endl;
    //cout << "Voisins" << endl;
    //cout << "i1 " << i1 << " j1 " << j1  << endl;
    //cout << "Verification mapDistance : " << (*this).mapDistance.at(make_pair(i,j))+1 << endl;
    //cout << "Verification mapDistance : " << (*this).mapDistance.at(make_pair(i1,j1)) << endl;

    if( ((*this).circuit[i1][j1]==0 || (*this).circuit[i1][j1]==9) && voisin && (*this).mapDistance.at(make_pair(i,j))!=INT_MAX && (*this).mapDistance.at(make_pair(i,j))+1<(*this).mapDistance.at(make_pair(i1,j1)) ){

      //cout <<"if passé "<<endl;
      if (j1 == 99) {
        //cout << "Creation de la paire " << i1 << " " << j1 << " avec comme distance " << (*this).mapDistance.at(make_pair(i,j))+1 << endl;

      }
      (*this).mapDistance[make_pair(i1,j1)]=(*this).mapDistance[make_pair(i,j)]+1;
      //cout << "distance +1 fait" << endl;


      (*this).mapPredecessor[make_pair(i1,j1)]=make_pair(i,j);
      //cout << "Nouveau précedent ajouté x1: " << i1 << " y1: " << j1 << " x2: " << i << " y2: " << j << endl;
      //cout << "ajout precedent " << endl;


      // on set l'arrivée
      if((*this).circuit[i1][j1]==9 && !PremiereArriveeTrouvee){

        (*this).arrivee=make_pair(i1,j1); // temp maybe

        cout << "Je suis tombé sur la fin" << endl;
        PremiereArriveeTrouvee=true;
      }
    }

  }
  else{
    //cout << "Pas voisins" << endl;
    //cout << "else passé" << endl;
  }

}



vector<int> Dijkstra::DijkstraAlgo(){ // adjacency matrix

  int compteurMinDist = 0;


    // init
    initDijkstra();

    // endInit


    int numberIteration=0;  //Nombre de pixels visités avant d'arriver à la fin
    while (!toutSommetsVisites()) {

        pair<int,int> m = (*this).minDist(); // sommet m

        compteurMinDist++;

        //cout << "compteurMinDist : " << compteurMinDist << " | " << (*this).mapDistance[make_pair(m.first,m.second)] << endl;

      //  cout << "sommet m -> x : " << m.first << " | y : " << m.second << endl;

      //  (*this).Tset[m]=true; // on prive Q de m en signifiant qu'il a été visité

        (*this).circuit[m.first][m.second] = 1;


        for(int i = m.first - 1; i <= m.first+1; i++ ){
          for(int j = m.second - 1; j <= m.second+1; j++ ){
            if(i >=0 && j >=0 && i < (int)(*this).circuit.size() && j < (int)(*this).circuit[m.first].size())
              numberIteration++;
              maj_distances(m.first, m.second, i, j);
          }
        }

        //Optimisation -> quand on a trouvé l'arrivée pas besoin de calculer les distances pour les autres points
        if (PremiereArriveeTrouvee){
          break;
        }
        
        
    }


  vector<int> vitesses = chemin();
  return vitesses;


}


vector<int> Dijkstra::chemin(){

  cout << "Affichage chemin" << endl;

  map<pair<int,int>,pair<int,int> > pred = (*this).mapPredecessor; // map des predecesseurs

  vector<pair<int,int> > listPoints; // liste de tt les points du chemin

  pair<int,int> Sdeb = make_pair((*this).x_depart,(*this).y_depart); // point de depart

  pair<int,int> currentSommet = (*this).arrivee;

  cout << "S deb -> x : " << Sdeb.first << " | y : " << Sdeb.second << endl;


  cout << "----------------------------------------------------------" << endl;

  bool isValid = true;

  while(isValid){
    listPoints.insert(listPoints.begin(), currentSommet);
    currentSommet = mapPredecessor[make_pair(currentSommet.first, currentSommet.second)];
    if(currentSommet.first == Sdeb.first && currentSommet.second == Sdeb.second)
      isValid = false;
  }

  listPoints.insert(listPoints.begin(), Sdeb);



  cout << "nombre d'éléments : " << (int) listPoints.size() << endl;
  cout << "predecesseur du dernier element : (" << mapPredecessor[make_pair(99, 99)].first <<  "," << mapPredecessor[make_pair(99, 99)].second <<") \n" << endl;



  // Affichage
  for(int i = 0; i < (int) listPoints.size(); i++)

    cout << "(" << listPoints[i].first << "," << listPoints[i].second << ")" << "\n";


  cout << endl;

  // Affichage passé ou pas

  cout << "Affichage circuit point passé(s)" << "\n" << endl;

  for(size_t i =0; i < (*this).circuit.size(); i++){
    for(size_t j = 0; j < (*this).circuit[i].size(); j++){
      cout << (*this).circuit[i][j] << " ";
    }
    cout << endl;
  }

  // Affichage distance from Sdeb

  cout << "Affichage ciruit point passé(s)" << "\n" << endl;

  for(size_t i =0; i < (*this).circuit.size(); i++){
    for(size_t j = 0; j < (*this).circuit[i].size(); j++){
      if ((*this).mapDistance[make_pair(i,j)] == INT_MAX){
        cout << '_' << " ";
      }
      else{
      cout << (*this).mapDistance[make_pair(i,j)] << " ";
      }
    }
    cout << endl;
  }

  //Creation d'une image de tous les points sur lesquels on est passé
  png::image< png::rgb_pixel > image("mulholland_drive.png");
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
  image.write("output.png");



  return getVitessesDijkstra(listPoints);

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

    /*
    cout << "----------------------------------" << endl;
    cout << "PAct x = "  << point.first << endl;
    cout << "PAct y = "  << point.second << endl;
    cout << "PPrec x = "  << x_prec << endl;
    cout << "PPrec y = "  << y_prec << endl;
    cout << "dif x = "  << dif_x << endl;
    cout << "dif y = "  << dif_y << endl;
    cout << "vit x = "  << v_x << endl;
    cout << "vit y = "  << v_y << endl;
    cout << "----------------------------------" << endl;
    */
    x_prec = point.first;
    y_prec = point.second;
  }



  return vitesses;
}


// destructeur
Dijkstra::~Dijkstra(){
  cout<<"Destruction de Dijkstra" <<endl;
}
