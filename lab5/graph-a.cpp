#include <iostream>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

class Graph{
	int Num_Vert;
	list<int> *graph;
	bool *visited;
	vector<vector<pair<int,int>>> wide_graph;
	int size_wg;

	public:
	Graph(int size){
		Num_Vert = size;
		graph = new list<int>[size];
		visited = new bool[size];
		wide_graph.reserve(size);
	}

	void add(int v1, int v2){
		graph[v1].push_front(v2);
		graph[v2].push_front(v1);
	}
	void add(int v1, int v2, int width){
		if (size_wg==0) size_wg=Num_Vert;
		wide_graph[v1].push_back(make_pair(v2,width));
		wide_graph[v2].push_back(make_pair(v1,width));
	}

	void clear_visited(){for(int i=0; i<Num_Vert;i++) visited[i]=false;}

	void s_depth(int start){
		visited[start] = true;
		list<int> newlist = graph[start];

		cout<<start<<" ";

		for (int i : newlist){
			if (!visited[i]) s_depth(i);
		}
	}

	void s_width(int start){
		queue<int> queue;
		clear_visited();
		visited[start]=true;
		queue.push(start);

		cout << "s_width: " << endl;
		while(!queue.empty()){
			int vert = queue.front();
			cout<<vert<<" ";
			queue.pop();
			list<int> newlist = graph[vert];

			for (int i : newlist){
				if (!visited[i]){
					visited[i]=true;
					queue.push(i);
				}
			}
		}
		clear_visited();
	}

	void s_Dijkstra(int start){
		cout << "Dijkstra: " << endl;
		if (size_wg==0) {
			cout<< "Empty vector"<<endl;
			return;
		}
		int size=size_wg;
		int INF = size*10000;
		vector<int> D(size, INF);
		visited = new bool[size];

		D[start] = 0;
		for (int i = 0; i < size; i++){
			int minInd=0;
			int min = INF;
			for (int j=0;j<size;j++){
				if(D[j]<min && !visited[j]){
					min=D[j];
					minInd=j;
				}
			}
			visited[minInd]=true;
			for (pair<int,int> p: wide_graph[minInd]){
				int u = p.first;
				int w = p.second;
				if (D[u]>D[minInd]+w) 
					D[u]=D[minInd]+w;
			}
		}
		for (int i = 0; i<size; i++){
			if (D[i]!=INF) cout<<start<< "->" << i <<"="<<D[i]<<endl;
			else cout<<"path not found"<<endl;
		}
			
	}

	void FloydWarshall(){
		cout << "FloydWarshall: " << endl;
		if (size_wg==0) {
			cout<< "Empty vector"<<endl;
			return;
		}
		int D[size_wg][size_wg];
		int INF = size_wg*10000;
		for (int i = 0; i < size_wg; i++){
			for (int j = 0; j < size_wg; j++){
				if (i==j) D[i][j]=0;
				else D[i][j]=INF;
			}
		}
		for (int i = 0; i < size_wg; i++){
			for (pair<int,int> p: wide_graph[i]){
				D[i][p.first]=p.second;
			}
		}

		for (int k = 0; k < size_wg; k++){
			for (int i = 0; i < size_wg; i++){
				for (int j = 0; j < size_wg; j++){
					D[i][j] = min(D[i][j], D[i][k]+D[k][j]);
				}
			}
		}
		
		for (int i = 0; i < size_wg; i++){
			for (int j = 0; j < size_wg; j++){
				cout<<D[i][j]<<" ";
			}
			cout << endl;
		}
	}

	void Prim(){
		cout << "Prim: " << endl;
		if (size_wg==0) {
			cout<< "Empty vector"<<endl;
			return;
		}
		int D[size_wg];
		int Parent[size_wg];
		visited = new bool[size_wg];
		int start = 0;
		int INF = size_wg*10000;
		for (int v = 0; v < size_wg; v++){
			D[v] = INF;
			Parent[v] = 0;
			visited[v] = false;
		}
		D[start] = 0;

		for (int i = 0; i < size_wg; i++){
			int minInd=0;
			int min = INF;
			for (int n=0; n<size_wg ; n++){
				if(D[n]<min && !visited[n]){
					min=D[n];
					minInd=n;
				}
			}
			visited[minInd] = true;
			for (pair<int,int> p: wide_graph[minInd]){
				int v = p.first;
				int weight = p.second;
				if (weight < D[v] && visited[v]==false){
					D[v] = weight;
					Parent[v] = minInd;
				}
			}
		}
		for(int i = 0; i < size_wg; i++){cout << "(" << Parent[i] << ", " << i << ")"<<endl;}
	}
};

int main(){
	// Graph gr1(5);
	// gr1.add(0,1);
	// gr1.add(0,2);
	// gr1.add(0,3);
	// gr1.add(1,2);
	// gr1.add(2,4);


	// Graph gr2(7);
	// gr2.add(0,1,2);
	// gr2.add(0,3,4);
	// gr2.add(0,2,1);
	// gr2.add(0,5,6);
	// gr2.add(1,4,3);
	// gr2.add(1,3,1);
	// gr2.add(2,3,2);
	// gr2.add(2,5,4);
	// gr2.add(3,6,1);
	// gr2.add(5,6,7);
	// gr2.add(4,6,4);

	// gr1.s_depth(0);
	// cout<<endl;
	// gr1.s_width(0);
	// cout<<endl;
	// gr2.s_Dijkstra(3);
	// cout<<endl;

	// Graph gr3(7);
	// gr3.add(0,1,1);
	// gr3.add(0,2,2);
	// gr3.add(0,3,4);
	// gr3.add(0,1,1);
	// gr3.add(1,3,2);
	// gr3.add(1,4,5);
	// gr3.add(2,3,7);
	// gr3.add(2,6,1);
	// gr3.add(2,5,4);
	// gr3.add(3,4,1);
	// gr3.add(3,6,1);

	// gr3.FloydWarshall();
	// cout<<endl;

	Graph gr4(7);
	gr4.add(0,1,2);
	gr4.add(0,2,1);
	gr4.add(0,3,3);
	gr4.add(0,5,6);
	gr4.add(1,3,1);
	gr4.add(1,4,3);
	gr4.add(2,3,2);
	gr4.add(2,5,3);
	gr4.add(3,6,1);
	gr4.add(4,6,4);
	gr4.add(5,6,7);

	gr4.Prim();

	return 0;
}
