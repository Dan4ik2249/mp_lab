#include <iostream>
#include <map>
#include <vector>
#include <queue>

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

    void split(Node *n){
        int count = 2*t-1;
        Node *new_node = new Node(t);
        new_node->parent = n->parent;
        
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
            cout << new_root->childr.size() << " - new root" <<endl;

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

    void helpInsert(Node *n, T key, K data){
        if (n!=NULL){
            if (n->mp.size() == 2*t-1) {
                printf("split run\n");
                split(n);
                printf("split end\n");
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


void print_leaves_by_level() {
    if(root == NULL) {
        return;
    }

    std::queue<Node*> nodes;
    nodes.push(root);

    while(!nodes.empty()) {
        Node *current_node = nodes.front();
        nodes.pop();

        // Если узел - лист
        if(current_node->leaf == 1) {
            typename map<T, K>::iterator it = current_node->mp.begin();
            for(; it != current_node->mp.end(); it++) {
                cout << "Key: " << it->first << ", Value: " << it->second << '\n';
            }
        }

        // Если узел не является листом - добавляем его потомков в очередь
        else {
            for(int i = 0; i < current_node->childr.size(); i++) {
                nodes.push(current_node->childr[i]);
            }
        }
    }
}


public:
    int t;
    Node* root;

    btree_map(int rang){
        t = rang;
    };
    btree_map(btree_map *new_bt){
        new_bt->root = this->root;
    };
    int is_empty(){
        return root==NULL?1:0;
    }
    ~btree_map(){
        t = 0;
        root = NULL;
    };
};

int main(){
    btree_map<int, int> bt(2);
    bt.insert(3, 3);
    bt.insert(6, 3);
    bt.insert(2, 3);
    bt.insert(9, 3);
    printf("add 9\n");
    bt.insert(5, 3);
    printf("add 5\n");
    bt.insert(10, 3);
    bt.insert(11, 3);
    bt.insert(12, 3);
    bt.insert(13, 3);
    bt.insert(14, 3);
    bt.insert(15, 3);
    bt.insert(16, 3);
    bt.insert(17, 3);
    bt.insert(18, 3);
    bt.insert(19, 3);
    bt.insert(20, 3);

    bt.print_tree();
    //bt.print_leaves_by_level();

    return 0;
}