#include <iostream>


template<class T, class Y>
class Map{
    private:
        struct node{
            public:
                T key;
                Y data;
                node* left;
                node* right;
                int height;

                node(T key, Y data){
                    this->key = key;
                    this->data = data;
                    this->left = NULL;
                    this->right = NULL;
                    this->height = 1;
                }
        };

        node* clone(const node* n) {
            if (n == NULL) return NULL;

            node* new_node = new node(n->key, n->data);
            new_node->left = clone(n->left);
            new_node->right = clone(n->right);
            return new_node;
        }

        int height(node* n){
            if (n == NULL) return 0;
            return 1 + std::max(height(n->left), height(n->right));
        }
         int get_height(node* n) { return n?n->height:0; }

    int get_balance_fcktr(node* n) {
        if (n == NULL) return 0;
        return get_height(n->left) - get_height(n->right);
    }

    node* rotate_right(node* n) {
        node* tmp1 = n->left;
        node* tmp2 = tmp1->right;

        tmp1->right = n;
        n->left = tmp2;

        n->height = std::max(get_height(n->left), get_height(n->right)) + 1;
        tmp1->height = std::max(get_height(tmp1->left), get_height(tmp1->right)) + 1;

        return tmp1;
    }

    node* rotate_left(node* n) {
        node* tmp1 = n->right;
        node* tmp2 = tmp1->left;

        tmp1->left = n;
        n->right = tmp2;

        n->height = std::max(get_height(n->left), get_height(n->right)) + 1;
        tmp1->height = std::max(get_height(tmp1->left), get_height(tmp1->right)) + 1;

        return tmp1;
    }

    node* insert_node(node* n, T key, Y data) {
        if (n == NULL) return new node(key, data);

        if (key < n->key)
            n->left = insert_node(n->left, key, data);
        else if (key > n->key)
            n->right = insert_node(n->right, key, data);

        n->height = 1 + std::max(get_height(n->left), get_height(n->right));
        int balance = get_balance_fcktr(n);

        if (balance > 1 && key < n->left->key)return rotate_right(n);
        else if (balance > 1 && key > n->left->key) {
            n->left = rotate_left(n->left);
            return rotate_right(n);
        }

        if (balance < -1 && key > n->right->key)
            return rotate_left(n);
        else if (balance < -1 && key < n->right->key) {
            n->right = rotate_right(n->right);
 	    return rotate_left(n);
        }

        return n;
    }

    public:
        node* root;

        Map(){root = NULL;}
        Map(const Map& a){this->root = clone(a.root);}
         
        void insert(T key, Y data) {this->root = insert_node(root, key, data);}

        node* search(T key){
            node* curr = this->root;
            while(curr!=NULL){
                if(curr->key == key) {
                    return curr;
                } else if (key < curr->key){
                    curr = curr->left;
                } else {
                    curr = curr->right;
                }
            }
            return NULL;
        } 

        int is_empty(){
            if (this->root == NULL) return 0;
            if (this->root != NULL) return 1;
        }
        Y get_date(T key){
            if (search(key) != NULL) {
                return search(key)->data;
            } else {
                return 0;
            }
        }

        int height_helper(node* n) {
            if (n == nullptr) return 0;
            
            int left_height = height_helper(n->left);
            int right_height = height_helper(n->right);

            return std::max(left_height, right_height) + 1;
        }

        int get_height(){
            return height_helper(this->root);
        }

        void print_tree(node* n, int level = 0, char prefix = ' ') {
            if (n != nullptr) {
                print_tree(n->right, level + 1, '/');
                std::cout << std::string(level * 4, ' ') << prefix << n->key << std::endl;
                print_tree(n->left, level + 1, '\\');
            }
        }

        void del_all(){this->root = NULL;}
        ~Map(){this->root = NULL;}
};


int main(){
    Map<int, int> test;
    

    test.insert(2, 1);
    std::cout << "add(2)" << std::endl;
    test.print_tree(test.root);
    
    test.insert(4, 2);
    std::cout << "add(4)" << std::endl;
    test.print_tree(test.root);
    
    test.insert(3, 3);
    std::cout << "add(3)" << std::endl;
    test.print_tree(test.root);
    
    test.insert(5, 4);
    std::cout << "add(5)" << std::endl;
    test.print_tree(test.root);
    
    test.insert(7, 5);
    std::cout << "add(7)" << std::endl;
    test.print_tree(test.root);
    
    test.insert(6, 6);
    std::cout << "add(6)" << std::endl;
    test.print_tree(test.root);
    
    test.insert(9, 5);
    std::cout << "add(7)" << std::endl;
    test.print_tree(test.root);
    
 

     

     int a = 7;
    if (test.search(a) == NULL) {
        std::cout << a << " not exist" << std::endl;
    } else {
        std::cout << a << " is exist" << std::endl;
    }

    std::cout << "get data by key: " << test.get_date(a) << std::endl;
    std::cout << "height: " << test.get_height() << std::endl;

    test.del_all();
    test.print_tree(test.root);

    return 0;
}
