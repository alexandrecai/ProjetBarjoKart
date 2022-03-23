#include "dijkstra.hpp"

using namespace std;

// constructeur
Dijkstra::Dijkstra(vector<vector<int>> _circuit, int _x_depart, int _y_depart){
  (*this).circuit = _circuit;
  (*this).x_depart = _x_depart;
  (*this).y_depart = _y_depart;
}


pair<int, int> Dijkstra::minDist() // finding minimum distance
{
  /*
    int minimum=INT_MAX; // INT_MAX => valeur max d'un int en C++
		int indexSommet;

    for(int k=0;k<6;k++)
    {
        if(Tset[k]==false && distance[k]<=minimum)
        {
            minimum=distance[k];
            indexSommet=k;
        }
    }
*/

  //new version

    int minimum=INT_MAX;
    pair<int, int> indexSommet;

    for(int i = 0; i < (int) (*this).circuit.size(); i++){
      for(int j = 0; j < (int) (*this).circuit[i].size(); j++){
        if(circuit[i][j]==0 && mapDistance.at(make_pair(i,j)) <= minimum){

          minimum = mapDistance.at(make_pair(i,j));
          //(*this).mapDistance[make_pair(i,j)]=INT_MAX;
          indexSommet = make_pair(i,j);

        //  cout << "minimum : " << minimum << endl;

        //  cout << " first : " << indexSommet.first << " | second : " << indexSommet.second  <<  endl;

        }
      }
    }



    return indexSommet;
}



bool Dijkstra::toutSommetsVisites(bool Tset[]){
/*
  for(int i = 0; i < 6; i++){
		if(Tset[i]==false)
			return false;
	}

	return true;
  */

  // new version

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


void Dijkstra::initDijkstra(int distance[], bool Tset[], int src){

/*
  for(int k = 0; k<6; k++){
      distance[k] = INT_MAX;
      Tset[k] = false;
  }
  distance[src] = 0;   // distance du sommet source initialisée à 0 car distance à lui-même "nulle"

*/

  // new version

  for(int i = 0; i < (int) (*this).circuit.size(); i++){
    for(int j = 0; j < (int) (*this).circuit[i].size(); j++){
      if(!(circuit[i][j]==2)){
        (*this).mapDistance[make_pair(i,j)]=INT_MAX;
      }
    }
  }

//  cout << "map [4] [5] : " << mapDistance.at(make_pair(4,5)) << endl;

  mapDistance[make_pair((*this).x_depart,(*this).y_depart)]=0;

}






void Dijkstra::maj_distances(int m, int k, int graph[6][6], int i, int j, int i1, int j1){
  // maj distances
  if(!(*this).Tset[k] && graph[m][k] && (*this).distance[m]!=INT_MAX && (*this).distance[m]+graph[m][k]<(*this).distance[k])
  /*
    liste des conditions :
      - si k n'a pas été visité -> !Tset[k]
      - si k est voisin de m -> graph[m][k]
      - s'il existe un chemin depuis m jusqu'à Sdeb -> distance[m]!=INT_MAX
      - si k n'a pas été visité ou que chemin(de Sdeb à k) passe par un plus long chemin-> distance[m]+graph[m][k]<distance[k]
  */
      (*this).distance[k]=(*this).distance[m]+graph[m][k];


  // new version

  bool voisin = false;

  if(i1==i+1 && j1==j && i !=99){
    voisin = true;
  //  cout << "i1==i+1 && j1==j && i !=99" << endl;
  }


  if(i1 == i-1 && j1==j && i!=0){
    voisin = true;
  //  cout << "i1 == i-1 && j1==j && i!=0" << endl;
  }

  if(j1==j+1 && i1==i && j != 99){
    voisin = true;
  //  cout << "j1==j+1 && i1==i && j != 99" << endl;
  }


  if(j1 == j-1 && i1==i && j!=0){
    voisin = true;
  //  cout << "j1 == j-1 && i1==i && j!=0" << endl;
  }


  //test
  if(i==99 && j==1){
    cout << "bool voisin : " << voisin << endl;
  }


  if(voisin) {
    if( ((*this).circuit[i1][j1]==0 || (*this).circuit[i1][j1]==9) && voisin && (*this).mapDistance.at(make_pair(i,j))!=INT_MAX && (*this).mapDistance.at(make_pair(i,j))+1<(*this).mapDistance.at(make_pair(i1,j1)) ){
      (*this).mapDistance[make_pair(i1,j1)]=(*this).mapDistance[make_pair(i,j)]+1;

      (*this).mapPredecessor[make_pair(i1,j1)]=make_pair(i,j);


      // on set l'arrivée
      if((*this).circuit[i1][j1]==9){

        (*this).arrivee=make_pair(i1,j1); // temp maybe

        cout << "Je suis tombé sur la fin" << endl;

      }

      // cf. tests
      if(i1==99 && j1==1 && i == 0 && j == 0){
        cout << "condition normalement jamais soulevée" << endl;
      }

    }

  }
  else{
  //  cout << "pas voisin" << endl;
  }

}








void Dijkstra::DijkstraAlgo(int graph[6][6],int src){ // adjacency matrix

    cout << "predecesseur du dernier element : (" << mapPredecessor[make_pair(99, 99)].first <<  "," << mapPredecessor[make_pair(99, 99)].second <<") \n" << endl;

    // init
    initDijkstra((*this).distance, (*this).Tset, src);

    // endInit


    while (!toutSommetsVisites((*this).Tset)) {

        pair<int,int> m = (*this).minDist(); // sommet m

      //  cout << "sommet m -> x : " << m.first << " | y : " << m.second << endl;

      //  (*this).Tset[m]=true; // on prive Q de m en signifiant qu'il a été visité

        (*this).circuit[m.first][m.second] = 1;

      //  cout << "sommet visité" << endl;

        for(int i = m.first - 1; i <= m.first+1; i++ ){
          for(int j = m.second - 1; j <= m.second+1; j++ ){
            maj_distances(1,1,graph, m.first, m.second, i, j);
          }
        }


        /*

        for(int k = 0; k<6; k++){ // pour tout les sommets k voisins de m
            maj_distances(m,k, graph);
        }

        */
    }

  //  cout << "dijkstra fini" << '\n' << endl;


  cout << "predecesseur du dernier element : (" << mapPredecessor[make_pair(99, 99)].first <<  "," << mapPredecessor[make_pair(99, 99)].second <<") \n" << endl;

    chemin();
/*

		// affichage
    cout<<"Vertex\t\tDistance from source vertex"<<endl;
    for(int k = 0; k<6; k++)
    {
        char str=65+k;
        cout<<str<<"\t\t\t"<<(*this).distance[k]<<endl;
    }
*/

}


void Dijkstra::chemin(){

  cout << "Affichage chemin" << endl;

  map<pair<int,int>,pair<int,int>> pred = (*this).mapPredecessor; // map des predecesseurs

  vector<pair<int,int>> listPoints; // liste de tt les points du chemin

  pair<int,int> Sdeb = make_pair((*this).x_depart,(*this).y_depart); // point de depart


  cout << "arrivee en 99,99 : " << (*this).circuit[99][99] << " . " << endl;

  (*this).arrivee=make_pair(99,99);

  pair<int,int> currentSommet = (*this).arrivee;

  cout << "S deb -> x : " << Sdeb.first << " | y : " << Sdeb.second << endl;

  while(Sdeb.first != currentSommet.first && Sdeb.second != currentSommet.second){
    listPoints.insert(listPoints.begin(), currentSommet);
    currentSommet = mapPredecessor[make_pair(currentSommet.first, currentSommet.second)];
  }

  listPoints.insert(listPoints.begin(), Sdeb);



  cout << "premier element : " << listPoints[0].first <<"," << listPoints[0].second << "\n" << endl;

  cout << "nombre d'éléments : " << (int) listPoints.size() << endl;


  cout << "predecesseur du dernier element : (" << mapPredecessor[make_pair(99, 99)].first <<  "," << mapPredecessor[make_pair(99, 99)].second <<") \n" << endl;

  // Affichage
  for(int i = 0; i < (int) listPoints.size(); i++)
    cout << "(" << listPoints[i].first << "," << listPoints[i].second << ")" << "\n";


  cout << endl;
}


// destructeur
Dijkstra::~Dijkstra(){
  cout<<" dijkstra detruit" <<endl;
}
