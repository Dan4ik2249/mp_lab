#include <iostream>
#include <cstring>

template<typename T, typename K>
class Map{
    public:
        struct node{
            node* p;
            K key;
            T data;
            int height;
            node* left;
            node* right;
            node(K key, T data, node* parent){
                this->key = key;
                this->data = data;
                left = NULL;
                right = NULL;
                height = 0;
                p = parent;
            }
        };
        node* root;

        int height(node* p){return p?p->height:0;}

        int height_helper(node* n) {
            if (n == nullptr) return 0;
            
            int leftHeight = height_helper(n->left);
            int rightHeight = height_helper(n->right);

            return std::max(leftHeight, rightHeight) + 1;
        }

        int get_height(){
            return height_helper(this->root);
        }

        int setBalance(node* p){ return height_helper(p->right)-height_helper(p->left);}

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

        void insert(K key, T data){
            node* n = new node(key, data, NULL);
            if (root == NULL){
                root = n;
            }
            else{
                root = insertTo(root, n);
            }
            
        }
        
        node* insertTo(node* p, node* n){
            if (n->key >= p->key){
                if(p->right == NULL){
                    p->right = n;
                    n->p = p;
                } 
                else{
                    insertTo(p->right, n);
                }
                p->height+=1;
            }
            else{
                if(p->left == NULL){
                    p->left = n;
                    n->p = p;
                } 
                else{
                    insertTo(p->left, n);
                }
                p->height-=1;
            }
            n = balanceTree(root);
            return n;
        }

        node* balanceTree(node* &n){
            if(n != NULL){
                if (n->height > 1){
                    if(n->key > n->left->key){
                        std::cout << n->key << std::endl;
                        return left_rotate(n);
                    } else {
                        right_rotate(n->right);
                        return left_rotate(n);
                    }
                }
                if (n->height < -1){
                    if(n->key < n->left->key){
                        return right_rotate(n);
                    } else {
                        left_rotate(n->left);
                        return right_rotate(n);
                    }
                }
                balanceTree(n->right);
                balanceTree(n->left);
            }
            return n;
        }


        void print_tree(node* node, int level = 0, char prefix = ' ') {
            if (node != nullptr) {
                print_tree(node->right, level + 1, '/');
                std::cout << std::string(level * 4, ' ') << prefix << node->key << std::endl;
                print_tree(node->left, level + 1, '\\');
            }
        }
        void prt(){std::cout << root->key << std::endl;}
};

int main(){
    printf("main");
    Map<int, int> test;
    std::cout << "create" << std::endl;
    test.insert(2,2);
    std::cout << "1" << std::endl;
    test.insert(4,2);
    std::cout << "2" << std::endl;
    test.insert(3,2);
    std::cout << "added" << std::endl;
    test.print_tree(test.root);
    

    
    // for (int i = 1; i < 10; i++){
    //     test.insert(i, i*2);
    //     std::cout << i << std::endl;
    // }
}
