#include <iostream>
#include <queue>
using namespace std;

struct Node {
    string key, value;
    Node* left;
    Node* right;
};

class BST_dic {
private:
    Node* root;

    Node* newNode(string key, string value) {
        return new Node{key, value, nullptr, nullptr};
    }

    Node* insert(Node* node, string key, string value) {
        if (!node) return newNode(key, value);
        if (key < node->key)
            node->left = insert(node->left, key, value);
        else if (key > node->key)
            node->right = insert(node->right, key, value);
        else
            node->value = value; // Update value for duplicate key
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, string key) {
        if (!node) return node;
        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    Node* search(Node* node, string key) {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return search(node->left, key);
        return search(node->right, key);
    }

    void inOrder(Node* node) {
        if (node) {
            inOrder(node->left);
            cout << node->key << ": " << node->value << endl;
            inOrder(node->right);
        }
    }

    void mirror(Node* node) {
        if (node) {
            swap(node->left, node->right);
            mirror(node->left);
            mirror(node->right);
        }
    }

    Node* copyTree(Node* node) {
        if (!node) return nullptr;
        Node* newRoot = newNode(node->key, node->value);
        newRoot->left = copyTree(node->left);
        newRoot->right = copyTree(node->right);
        return newRoot;
    }

    void levelOrder(Node* node) {
        if (!node) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            cout << temp->key << ": " << temp->value << "  ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        cout << endl;
    }

public:
    BST_dic() : root(nullptr) {}

    void insert(string key, string value) {
        root = insert(root, key, value);
    }

    void deleteKey(string key) {
        root = deleteNode(root, key);
    }

    void searchKey(string key) {
        Node* res = search(root, key);
        if (res)
            cout << res->key << ": " << res->value << endl;
        else
            cout << "Word not found." << endl;
    }

    void display() {
        inOrder(root);
    }

    void mirror() {
        mirror(root);
    }

    void copyDictionary() {
        Node* copiedRoot = copyTree(root);
        inOrder(copiedRoot);
    }

    void displayLevelOrder() {
        levelOrder(root);
    }
};

int main() {
    BST_dic dictionary;
    int choice;
    dictionary.insert("Glass", "Liquid Container");
    dictionary.insert("mouse", "coumputer interating object");
    string key, value;

    do {
        cout << "1. Insert\n2. Delete\n3. Search\n4. Display\n5. Mirror\n6. Copy\n7. Level Order\n8. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter word and meaning: ";
                cin >> key >> value;
                dictionary.insert(key, value);
                break;
            case 2:
                cout << "Enter word to delete: ";
                cin >> key;
                dictionary.deleteKey(key);
                break;
            case 3:
                cout << "Enter word to search: ";
                cin >> key;
                dictionary.searchKey(key);
                break;
            case 4:
                dictionary.display();
                break;
            case 5:
                dictionary.mirror();
                break;
            case 6:
                dictionary.copyDictionary();
                break;
            case 7:
                dictionary.displayLevelOrder();
                break;
        }
    } while (choice != 8);

    return 0;
}
