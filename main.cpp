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

    void rightRotate(Node*& r, Node*& x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;

        if (!x->parent) r = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->right = x;
        x->parent = y;
    }

    void fix(Node*& r, Node*& x) {
        while (x != r && x->parent->color == RED) {
            Node* p = x->parent;
            Node* g = p->parent;

            if (p == g->left) {
                Node* u = g->right;
                if (u && u->color == RED) {
                    g->color = RED;
                    p->color = BLACK;
                    u->color = BLACK;
                    x = g;
                } else {
                    if (x == p->right) {
                        leftRotate(r, p);
                        x = p;
                        p = x->parent;
                    }
                    rightRotate(r, g);
                    Color t = p->color;
                    p->color = g->color;
                    g->color = t;
                    x = p;
                }
