#include <iostream>

using namespace std;

struct node{
    int key;
    node* left;
    node* right;
    int height;
};

class BST{
    node *root;

    node* insert(node *rlt, int key){
        if(!rlt){
            node *nn = new node;
            nn->key = key;
            nn->left = NULL;
            nn->right = NULL;
            nn->height = 1;
            return nn;
        }
        if(key<rlt->key){
            rlt->left = insert(rlt->left, key);
        }
        else if(key>rlt->key){
            rlt->right = insert(rlt->right, key);
        }
        rlt->height = 1 + max(get_height(rlt->left), get_height(rlt->right));
        return(rlt);


    }

    int get_height(node *rlt){
        if(!rlt)
            return 0;
        return rlt->height;
    }

    node* minval(node* root){
        node* current = root;
        while(current->left != NULL){
            current = current->left;
        }
        return current;
    }

    node* delet(node* rlt, int key){
        if(!rlt){
            return rlt;
        }
        if(key<rlt->key){
            rlt->left = delet(rlt->left, key);
        }
        else if(key>rlt->key){
            rlt->right = delet(rlt->right, key);
        }
        else{
            if(!rlt->left && !rlt->right){
                delete rlt;
                return NULL;
            }
            else if(!rlt->right){
                node *temp = rlt->left;   
                delete rlt;
                return(rlt->left);
            }
            else{
                node *temp = rlt->right;
                temp = minval(temp);
                rlt-> key = temp->key;
                temp->left = delet(rlt->left, temp->key);
            }

        }
    }

    public:
    BST(){
        root->left = NULL;
        root->right = NULL;
        root->height = 0;
    }
};

int main(){
    BST bst;
    return(0);
}
