#include <iostream>
#include <cstring>

template <class K, class V>
class Hash_Map{
    private:
    struct Node{
        K key;
        V value;
        Node* next;
        Node(K key, V value){
            this->key = key;
            this->value = value;
            next = NULL;
        }

    };

    Node** arr;
    float count_key;
    float count_cell;
    int max_size;
    float alpha;

    int hash_func(K key){
        std::hash<K> hash_key;
        int h_key = hash_key(key) % max_size;
        return h_key;
    }

    void rehash(){
        Node** tmp = arr;
        max_size = max_size*2 + 1;
        arr = new Node*[max_size];
        delete_all();
        for(int i = 0; i < (max_size-1)/2; i++){
            Node* p = tmp[i];
            if (p==NULL) {
                continue;
            }
            else{
                while(p!=NULL){
                    add(p->key, p->value);
                    p = p->next;
                }
            }
        }
        for(int i = 0; i < (max_size-1)/2; i++){
            if (tmp[i]) delete tmp[i];
        }
        delete[] tmp;
    }

    public:

    Hash_Map(int max_size, float alpha){
        count_cell = 0;
        count_key = 0;
        this->max_size = max_size;
        this->alpha = alpha;
        arr = new Node*[max_size];
        for (int i = 0; i < max_size; i++){arr[i]=NULL;}
    }
    ~Hash_Map(){
        for(int i = 0; i < max_size; i++){
            if (arr[i]) delete arr[i];
        }
        delete[] arr;
    }

    void add(K key, V value){
        int h_key = hash_func(key);
        Node* n = new Node(key, value);
        if (arr[h_key] == NULL){
            arr[h_key] = n;
            count_key++;
            count_cell++;
        }
        else{
            Node* p = arr[h_key];
            while(p->next!=NULL){
                p = p->next;
            }
            p->next = n;
            count_key++;
        }
        if (count_cell!=0 && get_levelload() >= alpha) {rehash();}
    }

    void print_map(){
        for(int i = 0; i < max_size; i++){
            Node* p = arr[i];
            if (p==NULL) std::cout << "NULL";
            while(p!=NULL){
                std::cout << p->key << " ";
                p = p->next;
            }
            std::cout << std::endl;
        }
    }

    void delete_key(K key){
        int h_key = hash_func(key);
        Node* n = arr[h_key];
        if (n->key==key) {
            arr[h_key]=n->next;
            count_key--;
            if (arr[h_key]==NULL) count_cell--;
            return;
            }
        while(n->next->key!=key){
            if (n->next->next == NULL) {
                std::cout << "Key: " << key <<" - not found" << std::endl;
                return; 
            }
            n = n->next;
        }
        n->next = n->next->next;
        count_key--;
        if (arr[h_key]==NULL) count_cell--;
    }

    int get_count_key(){
        return count_key;
    }

    float get_levelload(){
        return count_cell==0?0:count_key/max_size;
    }

    float get_alpha(){
        return alpha;
    }

    int get_cell(){
        return count_cell;
    }

    void change_alpha(float alpha){
        while(get_levelload() >= alpha){rehash();}
        this->alpha = alpha;
    }

    void delete_all(){
        count_cell = 0;
        count_key = 0;
        for (int i = 0; i < max_size; i++){arr[i]=NULL;}
    }
};
