#include <iostream>
#include <cstring>

template<typename T, typename K>
class Map{
    public:
        struct node{
            K key;
            T data;
            int height;
            node* left;
            node* right;
            node(K key, T data){
                this->key = key;
                this->data = data;
                left = NULL;
                right = NULL;
                height = 0;
            }
        };
        node* root;

        int height(node* p){return p?p->height:0;}

        node* left_rotate(node* n){
            node* tmp1 = n->right;
            node* tmp2 = tmp1->left;
            tmp1->left = n;
            n->right = tmp2;
            return tmp1;
        }
        node* right_rotate(node* n){
            node* tmp1 = n->left;
            node* tmp2 = tmp1->right;
            tmp1->right = n;
            n->left = tmp2;
            return tmp1;
        }


    public:
        Map(){
            root = NULL;
        }

                node* insertTo(node* p, K key, T data){
            if(!p) return new node(key, data);
            if(key < p->key)
                p->left = insertTo(p->left, key, data);
            else
                p->right = insertTo(p->right, key, data);
            return balanceTree(p);
        }

        void fix_height(node* p){
            int hl = height(p->left);
            int hr = height(p->right);
            p->height = (hl>hr?hl:hr)+1;
        }

        node* balanceTree(node* p){
            fix_height(p);
            if(bfactor(p)==2){
                if(bfactor(p->right) < 0)
                    p->right = right_rotate(p->right);
                return left_rotate(p);
            }
            if(bfactor(p) == -2){
                if(bfactor(p->left) > 0 )
                    p->left = left_rotate(p->left);
                return right_rotate(p);
            }
            return p;
        }

        void insert(K key, T data){
            root = insertTo(root, key, data);
        }
        int bfactor(node* p){
            return height(p->right) - height(p->left);
        }


        void print_tree(node* node, int level = 0, char prefix = ' ') {
            if (node != nullptr) {
                print_tree(node->right, level + 1, '/');
                std::cout << std::string(level * 4, ' ') << prefix << node->key <<"(" << node->height << ")"<< std::endl;
                print_tree(node->left, level + 1, '\\');
            }
        }
        void prt(){std::cout << root->key << std::endl;}
};

int main(){
    printf("main\n");
    Map<int, int> test;
    std::cout << "add(2)" << std::endl;
    test.insert(2,2);
    test.print_tree(test.root);
    std::cout << "add(4)" << std::endl;
    test.insert(4,2);
    test.print_tree(test.root);
    std::cout << "add(3)" << std::endl;
    test.insert(3,2);
    test.print_tree(test.root);
    std::cout << "add(5)" << std::endl;
    
    test.insert(5,2);
    test.print_tree(test.root);
    std::cout << "add(7)" << std::endl;
    test.insert(7,2);
    test.print_tree(test.root);
    // std::cout << "add5" << std::endl;
    // test.insert(6,2);
    // test.print_tree(test.root);
    

    
    // for (int i = 1; i < 10; i++){
    //     test.insert(i, i*2);
    //     std::cout << i << std::endl;
    // }
}

