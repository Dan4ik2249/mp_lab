#include <iostream>
#include "graph_b.hpp"

int main(){
    // Graph_Alg gr(7);
    // gr.add(0, 1);
    // gr.add(0, 2);
    // gr.add(1, 3);
    // gr.add(2, 3);
    // gr.add(2, 5);
    // gr.add(3, 6);
    // gr.add(4, 5);
    // gr.add(5, 6);
    // gr.add(6, -1);
    // cout << "Taryan: " << endl;
    // gr.Taryan(0);
    // cout << endl;

    

    //Test for Cycle_alg
    Graph_Alg grph(6);
    // gr1.add2(0, 1);
    // gr1.add2(0, 4);
    // gr1.add2(1, 2);
    // gr1.add2(1, 5);
    // gr1.add2(1, 3);
    // gr1.add2(2, 3);
    // gr1.add2(2, 4);
    // gr1.add2(2, 5);
    // gr1.add2(3, 4);
    // gr1.add2(3, 5);
    // gr1.add2(4, 5);
    // cout << "Cycle_Alg: " << endl;
    // gr1.Cycle_Alg();
    // cout << endl;

    grph.add2(0, 1);
    grph.add2(0, 2);
    grph.add2(0, 3);
    grph.add2(0, 4);
    grph.add2(1, 2);
    grph.add2(1, 3);
    grph.add2(1, 4);
    grph.add2(2, 3);
    grph.add2(2, 5);
    grph.add2(3, 4);
    grph.add2(4, 5);
    cout << "Fleri: " << endl;
    grph.Fleri();
    cout << endl;

    // Graph_Alg gr2(8);
    // gr2.add(0, 1);
    // gr2.add(0, 3);
    // gr2.add(1, 2);
    // gr2.add(1, 4);
    // gr2.add(1, 6);
    // gr2.add(2, 5);
    // gr2.add(2, 6);
    // gr2.add(3, 0);
    // gr2.add(4, 3);
    // gr2.add(4, 5);
    // gr2.add(4, 7);
    // gr2.add(5, 6);
    // gr2.add(6, 2);
    // gr2.add(6, 7);
    // cout << "Kosaraju: " << endl;
    // gr2.Kosaraju();

    return 0;
}