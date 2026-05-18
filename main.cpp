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

    // Creates a new red node
    Node* create(int v) {
        Node* n = new Node;
        n->data = v;
        n->color = RED;
        n->left = n->right = n->parent = NULL;
        return n;
    }

    // Regular BST insert
    Node* insert(Node* r, Node* n) {
        if (!r) return n;

        if (n->data < r->data) {
            r->left = insert(r->left, n);
            r->left->parent = r;
        }
        else if (n->data > r->data) {
            r->right = insert(r->right, n);
            r->right->parent = r;
        }

        return r;
    }

    // Left rotation
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

    // Right rotation
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

    // Fixes red-black tree violations after insert
    void fix(Node*& r, Node*& x) {
        while (x != r && x->parent->color == RED) {
            Node* p = x->parent;
            Node* g = p->parent;

            // Parent is left child
            if (p == g->left) {
                Node* u = g->right;

                // Case 1: uncle is red
                if (u && u->color == RED) {
                    p->color = BLACK;
                    u->color = BLACK;
                    g->color = RED;
                    x = g;
                }
                else {
                    // Case 2: triangle
                    if (x == p->right) {
                        leftRotate(r, p);
                        x = p;
                        p = x->parent;
                    }

                    // Case 3: line
                    rightRotate(r, g);

                    p->color = BLACK;
                    g->color = RED;
                }
            }

            // Parent is right child
            else {
                Node* u = g->left;

                if (u && u->color == RED) {
                    p->color = BLACK;
                    u->color = BLACK;
                    g->color = RED;
                    x = g;
                }
                else {
                    if (x == p->left) {
                        rightRotate(r, p);
                        x = p;
                        p = x->parent;
                    }

                    leftRotate(r, g);

                    p->color = BLACK;
                    g->color = RED;
                }
            }
        }

        // Root must always be black
        r->color = BLACK;
    }

    // Searches for a value
    Node* searchNode(Node* r, int v) {
        if (!r || r->data == v) return r;

        if (v < r->data)
            return searchNode(r->left, v);

        return searchNode(r->right, v);
    }

    // Finds smallest node
    Node* min(Node* r) {
        while (r->left)
            r = r->left;

        return r;
    }

    // Removes a node
    Node* removeNode(Node* r, int v) {
        if (!r) return r;

        if (v < r->data)
            r->left = removeNode(r->left, v);

        else if (v > r->data)
            r->right = removeNode(r->right, v);

        else {
            // No children
            if (!r->left && !r->right) {
                delete r;
                return NULL;
            }

            // One right child
            if (!r->left) {
                Node* t = r->right;
                delete r;
                return t;
            }

            // One left child
            if (!r->right) {
                Node* t = r->left;
                delete r;
                return t;
            }

            // Two children
            Node* t = min(r->right);

            r->data = t->data;

            r->right = removeNode(r->right, t->data);
        }

        return r;
    }

    // Prints tree sideways
    void printTree(Node* r, int s) {
        if (!r) return;

        s += 8;

        printTree(r->right, s);

        cout << endl;
        for (int i = 8; i < s; i++) cout << " ";

        cout << r->data << (r->color == RED ? "R" : "B");

        // Shows parent node
        if (r->parent)
            cout << "(" << r->parent->data << ")";

        cout << endl;

        printTree(r->left, s);
    }

public:
    RBTree() {
        root = NULL;
    }

    // Adds value to tree
    void add(int v) {
        Node* n = create(v);

        root = insert(root, n);

        fix(root, n);
    }

    // Removes value from tree
    void remove(int v) {
        root = removeNode(root, v);

        if (root)
            root->color = BLACK;
    }

    // Returns true if value exists
    bool search(int v) {
        return searchNode(root, v);
    }

    // Reads values from file
    void read(const char* file) {
        ifstream f(file);

        char line[1000];

        f.getline(line, 1000);

        char* t = strtok(line, " ");

        while (t) {
            add(atoi(t));
            t = strtok(NULL, " ");
        }
    }

    // Prints the tree
    void print() {
        printTree(root, 0);
    }
};

int main() {
    RBTree t;

    char cmd[20];

    while (true) {
        cout << "\nadd remove search file print quit\n> ";

        cin >> cmd;

        if (!strcmp(cmd, "add")) {
            int x;
            cin >> x;
            t.add(x);
        }

        else if (!strcmp(cmd, "remove")) {
            int x;
            cin >> x;
            t.remove(x);
        }

        else if (!strcmp(cmd, "search")) {
            int x;
            cin >> x;

            if (t.search(x))
                cout << "found\n";
            else
                cout << "not found\n";
        }

        else if (!strcmp(cmd, "file")) {
            char name[100];
            cin >> name;
            t.read(name);
        }

        else if (!strcmp(cmd, "print")) {
            t.print();
        }

        else if (!strcmp(cmd, "quit")) {
            break;
        }
    }
}
