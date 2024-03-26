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
            //fix_height(tmp1);
            return tmp1;
        }
        node* right_rotate(node* n){
            node* tmp1 = n->left;
            node* tmp2 = tmp1->right;
            tmp1->right = n;
            n->left = tmp2;
            //fix_height(tmp1);
            return tmp1;
        }


    public:
        Map(){
            root = NULL;
        }

        void insert(K key, T data){
            node* n = new node(key, data);
            if (root == NULL){
                root = n;
            }
            else{
                root = insertTo(root, n);
                // insertTo(root, n);
            }
            
        }
        
        node* insertTo(node* p, node* n){
            if (n->key >= p->key){
                if(p->right == NULL){
                    p->right = n;
                } 
                else{
                    insertTo(p->right, n);
                }
                // p->height+=1;
                fix_height(p);
                
            }
            else{
                if(p->left == NULL){
                    p->left = n;
                } 
                else{
                    
                    insertTo(p->left, n);
                }
                // p->height-=1;
                fix_height(p);
            }
            n = balanceTree(root);
            
            fix_height(n);
            return n;
            //return balanceTree(root);
        }

        void fix_height(node* n){
            n->height=len_tree(n->right)-len_tree(n->left);
            if (n->left != 0) n->left->height=len_tree(n->left->right)-len_tree(n->left->left);
            if (n->right != 0) n->right->height=len_tree(n->right->right)-len_tree(n->right->left);
        }
        int len_tree(node* n){
            if (n == nullptr) {
                return 0;
            }
            return 1 + std::max(len_tree(n->left), len_tree(n->right));
        }

        node* balanceTree(node* n){ 
            if(n != NULL){
                if (n->height > 1){
                    std::cout << n->key << "-"<< n->height <<std::endl;
                    //std::cout << root->key << "-"<< root->height <<std::endl;
                    //if (n->right->height>1||n->right->height<-1) balanceTree(n->right);
                    if(height(n->right)>0){
                        return left_rotate(n);
                    } else {
                        n->right = right_rotate(n->right);
                        return left_rotate(n);
                    }
                }
                if (n->height < -1){
                    std::cout << n->key << "-" << n->height <<std::endl;
                    if(height(n->left)<0){
                        return right_rotate(n);
                    } else {
                        n->left = left_rotate(n->left);
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
                std::cout << std::string(level * 4, ' ') << prefix << node->key <<"(" << node->height << ")"<< std::endl;
                print_tree(node->left, level + 1, '\\');
            }
        }
        int is_empty(){
            if (this->root == NULL) return 0;
            if (this->root != NULL) return 1;
        }
        void del_all(){this->root = NULL;}
        ~Map(){this->root = NULL;}
        void prt(){std::cout<< "root: "<<root->key<<std::endl;}
};

int main(){
    printf("main\n");
    Map<int, int> test;
    std::cout << "add(2)" << std::endl;
    test.insert(2,2);
    test.print_tree(test.root);
    std::cout << "add(5)" << std::endl;
    test.insert(5,2);
    test.print_tree(test.root);
    std::cout << "add(3)" << std::endl;
    test.insert(3,2);
    test.print_tree(test.root);
    std::cout << "add(4)" << std::endl;
    
    test.insert(4,2);
    test.print_tree(test.root);
    std::cout << "add(7)" << std::endl;
    test.insert(7,2);
    test.print_tree(test.root);
    std::cout << "add(1)" << std::endl;
    test.insert(1,3);
    test.print_tree(test.root);

    std::cout << "add(8)" << std::endl;
    test.insert(8,2);
    test.print_tree(test.root);
    test.prt();

    // std::cout << "add(9)" << std::endl;
    // test.insert(9,2);
    // test.print_tree(test.root);
    // test.prt();
}
