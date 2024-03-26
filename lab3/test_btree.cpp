#include <iostream>
#include "btree_map.h"

using namespace std;

int main(){
    btree_map<int, int> bt(2);
    bt.insert(3, 1);
    bt.insert(6, 2);
    bt.insert(2, 3);
    bt.insert(9, 4);
    
    bt.insert(5, 6);
    
    bt.insert(10, 8);
    bt.insert(11, 9);
    bt.insert(12, 10);
    bt.insert(13, 11);
    bt.insert(14, 12);
    bt.insert(15, 13);
    bt.insert(16, 14);
    bt.insert(17, 15);
    bt.insert(18, 16);
    bt.insert(19, 17);
    bt.insert(20, 18);

    bt.print_tree();
    //bt.print_leaves_by_level();

    cout << "Search 15: " << bt.search(15) << endl;

    return 0;
}