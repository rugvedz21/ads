#include <iostream>
using namespace std;

struct Node {
    int score;
    int id;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
private:
    Node* root;

    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* newNode(int score, int id) {
        Node* node = new Node();
        node->score = score;
        node->id = id;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;  
        return node;
    }

    Node* RightRotation(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotation(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* insert(Node* node, int score, int id) {
        if (node == nullptr)
            return newNode(score, id);

        if (score < node->score)
            node->left = insert(node->left, score, id);
        else if (score > node->score)
            node->right = insert(node->right, score, id);
        else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && score < node->left->score)
            return RightRotation(node);

        if (balance < -1 && score > node->right->score)
            return leftRotation(node);

        if (balance > 1 && score > node->left->score) {
            node->left = leftRotation(node->left);
            return RightRotation(node);
        }

        if (balance < -1 && score < node->right->score) {
            node->right = RightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* root, int score) {
        if (root == nullptr)
            return root;

        if (score < root->score) {
            root->left = deleteNode(root->left, score);
        } else if (score > root->score) {
            root->right = deleteNode(root->right, score);
        } 
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } 
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->score = temp->score;
            root->id = temp->id;
            root->right = deleteNode(root->right, temp->score);
        }

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return RightRotation(root);

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotation(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotation(root->left);
            return RightRotation(root);
        }

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = RightRotation(root->right);
            return leftRotation(root);
        }

        return root;
    }

    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << "Player ID: " << root->id << ", Score: " << root->score << endl;
            inOrder(root->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int score, int id) {
        root = insert(root, score, id);
    }

    void deleteNode(int score) {
        root = deleteNode(root, score);
    }

    void display() {
        inOrder(root);
    }
};

int main() {
    AVLTree tree;

    tree.insert(10,13);
    tree.insert(20,10);
    tree.insert(30,22);
    tree.insert(25,30);

    cout << "Well Come to K's Game: " << endl;
    int choice = 0;
    do {
        cout << "1. Insert\n2. Delete\n3. Leaderboard\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter the player id to be inserted: ";
                int id;
                cin >> id;
                cout << "Enter the score to be inserted: ";
                int score;
                cin >> score;
                tree.insert(score, id);
                break;
            }
            case 2: {
                cout << "Enter the score to delete: ";
                int delScore;
                cin >> delScore;
                tree.deleteNode(delScore);
                break;
            }
            case 3:
                tree.display();
                break;
            default:
                break;
        }

    } while (choice != 4);

    return 0;
}
