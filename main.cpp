#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
};

class RBTree {
private:
    Node* root;

    Node* create(int v) {
        Node* n = new Node;
        n->data = v;
        n->color = RED;
        n->left = n->right = n->parent = NULL;
        return n;
    }
