#include "hash-map.hpp"
#include <iostream>

int main(){
    Hash_Map<char, int> hm(5, 2);
    hm.add('5', 1);
    hm.add('7', 2);
    //hm.add(10, 3);
    //hm.add(20, 4);
    //hm.add(25, 4);
    //hm.add(3, 4);
    //hm.add(6, 4);
    //hm.add(16, 4);
    //hm.add(17, 4);
    //hm.change_alpha(0.5);
    //hm.add(12, 4);
    //hm.delete_key(10);
    //hm.delete_key(7);
    hm.print_map();
    std::cout << "Key count: " << hm.get_count_key()<< std::endl;
    std::cout << "level load: " << hm.get_levelload()<< std::endl;
    std::cout << "alpha: " << hm.get_alpha()<< std::endl;
    std::cout << "Count cell: " << hm.get_cell()<< std::endl;
    return 0;
}
