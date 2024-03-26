#include <iostream>
#include <map>
#include <vector>

using namespace std;

template<class T, class K>
class btree_map
{
public:
    struct Node{
        map<T, K> mp;
        vector<Node*> childr;
        Node *parent;
        int leaf;
        
        Node(int t){
            childr.reserve(2*t);
            parent = NULL;
            leaf = 1;
        }
    };
    int t;
    Node* root;

    void split(Node *n){
        int count = 2*t-1;
        Node *new_node = new Node(t);
        new_node->parent = n->parent;
        new_node->leaf = n->leaf;
        
        typename map<T, K>:: iterator it1 = n->mp.begin();

        for (int i = 0; i < count/2; it1++, i++){
            new_node->mp[it1->first] = it1->second;
        }
        
        for (int i = 0; i < count/2; i++){
            it1 = n->mp.begin();
            n->mp.erase(it1);
        }
        
        if (n->childr.size()!=0){
            int size = n->childr.size();
            for (int i = 0; i < size/2; i++){
                new_node->childr[i]=n->childr[i];
                }
            n->childr.erase(n->childr.begin(), n->childr.begin()+size/2);
        }

        if (n->parent==NULL){
            Node* new_root = new Node(t);
            
            it1 = n->mp.begin();
            new_root->mp[it1->first]=it1->second;
            n->mp.erase(it1);
            
            new_root->childr.insert(new_root->childr.begin(), n);
            new_root->childr.insert(new_root->childr.begin(), new_node);

            n->parent = new_root;
            new_node->parent = new_root;
            new_root->leaf = 0;
            
            this->root = new_root;
        } else{
            it1 = n->mp.begin();
            n->parent->mp[it1->first]=it1->second;
            n->mp.erase(it1);
            int i = 0;
            while(n->parent->childr[i]!=n) i++;
            n->parent->childr.insert(n->parent->childr.begin() + i, new_node);
            }
        
        if (n->parent->mp.size() >= 2*t-1) split(n->parent);
    }

    void helpInsert(Node *n, T key, K data){
        if (n!=NULL){
            if (n->mp.size() == 2*t-1) {
                split(n);
            }
            if(n->leaf){n->mp[key]=data;}
            else{
                typename map<T, K> :: iterator it = n->mp.begin();
                size_t mp_size = n->mp.size();
                
                for (int j = 1; it!=n->mp.end(); it++, j++){
                    if (key < it->first ){
                        n = n->childr[j-1];
                        break;
                    }
                    if (j == mp_size && key > it->first){
                        if (n->childr[j]!=NULL){
                            n = n->childr[j];
                            break;
                        }
                    }
                }
                helpInsert(n, key, data);
            }
        }
    }

    void print_tree(){
        typename map<T, K> :: iterator it = root->mp.begin();
        for (int i = 0; it!=root->mp.end(); it++, i++){
            cout << i << ") Ключ " << it->first << ", значение " << it->second << endl;
        }
        cout << endl;
        typename map<T, K> :: iterator it1 = root->childr[1]->mp.begin();
        for (int i = 0; it1!=root->childr[1]->mp.end(); it1++, i++){
            cout << i << ") Ключ " << it1->first << ", значение " << it1->second << endl;
        }
        cout << endl;
        typename map<T, K> :: iterator it2 = root->childr[1]->childr[1]->mp.begin();
        for (int i = 0; it2!=root->childr[1]->childr[1]->mp.end(); it2++, i++){
            cout << i << ") Ключ " << it2->first << ", значение " << it2->second << endl;
        }
    }

public:
    btree_map(int rang){
        t = rang;
        root = NULL;
    };
    btree_map(btree_map *new_bt){
        new_bt->root = this->root;
    };

    void insert(T key, K data){
        if (root==NULL){
            Node *n = new Node(t);
            n->mp[key] = data;
            root = n;
            printf("create root\n");
        }
        else {
            helpInsert(root, key, data);
        }

    }

    K search(T key){
        Node *n = root;
        while(1){
            typename map<T, K> :: iterator it = n->mp.begin();
            size_t mp_size = n->mp.size();
            for (int j = 1; it!=n->mp.end(); it++, j++){
                if (key < it->first ){
                    if (n->leaf == 1) {return 0;}
                    n = n->childr[j-1];
                    
                    break;
                }
                if (j == mp_size && key > it->first){
                    if (n->leaf == 1) {return 0;}
                    n = n->childr[j];
                    break;
                }
                if (key == it->first) {return it->second;}
            }
        }
    }

    int is_empty(){
        return root==NULL?1:0;
    }
    void delete_all(){
        root = NULL;
    }
    ~btree_map(){
        t = 0;
        root = NULL;
    };
};