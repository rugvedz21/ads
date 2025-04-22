#include <iostream>
#include <queue>
using namespace std;

const int MAX = 2; 
const int MIN = 1;

struct BTreeNode {
    int keys[MAX + 1];
    BTreeNode* children[MAX + 2];
    int count;
    bool leaf;

    BTreeNode(bool isLeaf) {
        leaf = isLeaf;
        count = 0;
        for (int i = 0; i < MAX + 2; i++)
            children[i] = nullptr;
    }
};

class BTree {
    BTreeNode* root;


public:
    BTree() { root = new BTreeNode(true); }

    void insert(int key);
    void display();
    void remove(int key);
};

void splitRoot() {
    BTreeNode* oldRoot = root;
    BTreeNode* newRoot = new BTreeNode(false);
    newRoot->children[0] = oldRoot;
    splitNonRootChild(newRoot, 0, oldRoot);
    root = newRoot;
}

// Splits a non-root child node when it's full
void splitNonRootChild(BTreeNode* parent, int i, BTreeNode* child) {
    BTreeNode* newChild = new BTreeNode(child->leaf);
    newChild->count = MIN;

    // Copy the last MIN keys of child to newChild
    for (int j = 0; j < MIN; j++)
        newChild->keys[j] = child->keys[j + MIN + 1];

    // If not leaf, copy the last MIN+1 children
    if (!child->leaf) {
        for (int j = 0; j <= MIN; j++)
            newChild->children[j] = child->children[j + MIN + 1];
    }

    /// Shift all children of parent one position to the right to make space for the new child
    for (int j = parent->count; j >= i + 1; j--) {
        parent->children[j + 1] = parent->children[j];
    }
    // Link the new child to the parent
    parent->children[i + 1] = newChild;

    // Shift all keys of parent one position to the right to make space for the middle key
    for (int j = parent->count - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    // Move the middle key of the child up to the parent
    parent->keys[i] = child->keys[MIN];

    // Update the parent's key count
    parent->count++;
    // Update the original child's key count after split
    child->count = MIN;
}

// Insert a key into the B-Tree
void insert(int key) {
    if (root->count == MAX) {
        splitRoot();
    }
    insertNonFull(root, key);
}

// Insert a key into a node that is not full
void insertNonFull(BTreeNode* node, int key) {
    int i = node->count - 1;
    if (node->leaf) {
        // Find location and insert key
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->count++;
    } 
    else {
        // Find child to insert into
        while (i >= 0 && key < node->keys[i]) i--;
        i++;
        // If the child is full, split it
        if (node->children[i]->count == MAX) {
            splitNonRootChild(node, i, node->children[i]);
            if (key > node->keys[i]) i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void display() {
    cout << "Level order traversal:\n";
    levelOrderDisplay(root);
}

// Deletion is non-trivial in B-Trees; placeholder for now
void remove(int key) {
    cout << "Deletion of " << key << " not implemented.\n";
}

int main() {    
    BTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    tree.display();

    tree.remove(6); // Not implemented  
    return 0;
}
