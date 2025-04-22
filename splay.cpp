#include <iostream>
#include <stack>
#include <queue>
#include <climits>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;

    // ...existing code...

class SplayTree {
    private:
        Node* root;
    
        // Single right rotation (zig)
        Node* zig(Node* x) {
            Node* y = x->left;
            x->left = y->right;
            y->right = x;
            return y;
        }
    
        // Single left rotation (zag)
        Node* zag(Node* x) {
            Node* y = x->right;
            x->right = y->left;
            y->left = x;
            return y;
        }
    
        // Double right rotation (zig-zig)
        Node* zigZig(Node* x) {
            x = zig(x);
            return zig(x);
        }
    
        // Right then left rotation (zig-zag)
        Node* zigZag(Node* x) {
            x->left = zag(x->left);
            return zig(x);
        }
    
        // Left then right rotation (zag-zig)
        Node* zagZig(Node* x) {
            x->right = zig(x->right);
            return zag(x);
        }
    
        // Double left rotation (zag-zag)
        Node* zagZag(Node* x) {
            x = zag(x);
            return zag(x);
        }
    
        Node* splay(Node* root, int key) {
            if (root == nullptr || root->data == key)
                return root;
    
            // Key lies in left subtree
            if (key < root->data) {
                if (root->left == nullptr) return root;
    
                // Zig-Zig (Left Left)
                if (key < root->left->data) {
                    root->left->left = splay(root->left->left, key);
                    root = zigZig(root);
                }
                // Zig-Zag (Left Right)
                else if (key > root->left->data) {
                    root->left->right = splay(root->left->right, key);
                    root = zigZag(root);
                }
                else {
                    root = zig(root);
                }
                return root;
            }
            // Key lies in right subtree
            else {
                if (root->right == nullptr) return root;
    
                // Zag-Zag (Right Right)
                if (key > root->right->data) {
                    root->right->right = splay(root->right->right, key);
                    root = zagZag(root);
                }
                // Zag-Zig (Right Left)
                else if (key < root->right->data) {
                    root->right->left = splay(root->right->left, key);
                    root = zagZig(root);
                }
                else {
                    root = zag(root);
                }
                return root;
            }
        }
    
    // ...rest of the code remains unchanged...

    Node* findMax(Node* node) {
        while (node->right) node = node->right;
        return node;
    }

public:
    SplayTree() : root(nullptr) {}

    void insert(int key) {
        if (!root) {
            root = new Node(key);
            return;
        }

        root = splay(root, key);

        if (key < root->data) {
            Node* newNode = new Node(key);
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullptr;
            root = newNode;
        } else if (key > root->data) {
            Node* newNode = new Node(key);
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullptr;
            root = newNode;
        }
    }

    void deleteNode(int key) {
        if (!root) return;

        root = splay(root, key);

        if (root->data != key) {
            cout << "Node " << key << " not found\n";
            return;
        }

        Node* temp;
        if (!root->left) {
            temp = root;
            root = root->right;
        } else {
            temp = root;
            Node* leftSubtree = root->left;
            root = splay(leftSubtree, findMax(leftSubtree)->data);
            root->right = temp->right;
        }
        delete temp;
        cout << "Node " << key << " deleted\n";
    }

    void levelOrder() {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }

        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            cout << temp->data << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        cout << endl;
    }

    void display() {
        levelOrder();
    }

    Node* Search(int key) {
        if (root == nullptr) {
            cout << "Empty Tree" << endl;
            return nullptr;
        }
    
        root = splay(root, key);
    
        if (root && root->data == key) {
            cout << "Found node " << key << " in the tree." << endl;
            return root;
        } else {
            cout << "Could not find node " << key << " in the tree." << endl;
            return nullptr;
        }
    }
    
};

int main() {
    SplayTree tree;

    tree.insert(10);
    tree.insert(90);
    tree.insert(5);
    tree.insert(60);
    tree.insert(23);
    tree.insert(51);

    cout<<"\nDisplaying tree before search  : "<<endl;
    tree.display();

    cout<<endl;
    tree.Search(5);

    cout<<"\nDisplaying tree after search  : "<<endl;
    tree.display();

    cout<<"\nDeleting a node : ";
    tree.deleteNode(5);

    return 0;
}
