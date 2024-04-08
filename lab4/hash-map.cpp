#include <iostream>

template <class K, class V>
class Hash_Map{
    private:
    struct Node{
        K key;
        V value;
        Node* next;
        Node(){
            key = 0;
            value = 0;
            next = NULL;
        }

    };

    Node** arr;
    int c_key;
    int c_cell;
    int max_count;
    int alpha;

    Hash_Map(int max_count){
        c_cell = 0;
        c_key = 0;
        this.max_count = max_count;
        alpha = 0;
        arr = new Node*[max_count];
        for (int i = 0; i < max_count; i++){arr[i]=nullptr;}
    }
};

