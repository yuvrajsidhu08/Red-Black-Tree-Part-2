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

    Node* insertBST(Node* r, Node* n) {
        if (!r) return n;
        if (n->data < r->data) {
            r->left = insertBST(r->left, n);
            r->left->parent = r;
        } else if (n->data > r->data) {
            r->right = insertBST(r->right, n);
            r->right->parent = r;
        }
        return r;
    }

    void leftRotate(Node*& r, Node*& x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;

        if (!x->parent) r = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }
