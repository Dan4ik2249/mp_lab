#include <iostream>
#include "graph-a.hpp"

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

	Graph gr3(7);
	gr3.add(0,1,1);
	gr3.add(0,2,2);
	gr3.add(0,3,4);
	gr3.add(0,1,1);
	gr3.add(1,3,2);
	gr3.add(1,4,5);
	gr3.add(2,3,7);
	gr3.add(2,6,1);
	gr3.add(2,5,4);
	gr3.add(3,4,1);
	gr3.add(3,6,1);

	gr3.FloydWarshall();
	cout<<endl;

	// Graph gr4(7);
	// gr4.add(0,1,2);
	// gr4.add(0,2,1);
	// gr4.add(0,3,3);
	// gr4.add(0,5,6);
	// gr4.add(1,3,1);
	// gr4.add(1,4,3);
	// gr4.add(2,3,2);
	// gr4.add(2,5,3);
	// gr4.add(3,6,1);
	// gr4.add(4,6,4);
	// gr4.add(5,6,7);

	// gr4.Prim(0);
	// gr4.Kruskal();

	return 0;
}
