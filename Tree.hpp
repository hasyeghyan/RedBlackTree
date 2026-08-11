#ifndef Tree_HPP
#define Tree_HPP

#include <iostream>
#include <vector>

class Tree {
    private:
        enum Color{Black, Red};

        struct Node {
            int val;
            Color color;
            Node* left;
            Node* right;
            Node* parent;

            Node(int val = 0) : val{val}, left{nullptr}, right{nullptr}, parent{nullptr}, color{Color::Red} {}
        };
         
        class Iter {
            private:
                Node* curr;
                Tree* tree;
            public:
                friend class Tree;
                Iter(Node* node, Tree* t) : curr(node), tree{t} {}

                bool operator==(const Iter& other) const { return tree == other.tree && curr == other.curr; }
                bool operator!=(const Iter& other) const { return !(*this == other); }

                Iter& operator++() {
                    if (curr == tree->NIL) return *this;
                    if (curr->right != tree->NIL) {
                        curr = curr->right;
                        while (curr->left != tree->NIL) curr = curr->left;
                    } else {
                        Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                Iter operator++(int) {
                    Iter tmp = *this;
                    ++(*this);
                    return tmp;
                }

                Iter& operator--() {
                    if (curr == tree->NIL) {
                        curr = tree->getMax(tree->root);
                        return *this;
                    }

                    if (curr->left != tree->NIL) {
                        curr = curr->left;
                        while (curr->right != tree->NIL) curr = curr->right;
                    } else {
                        Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                Iter operator--(int) {
                    Iter tmp(*this);
                    --(*this);
                    return tmp;
                }

                int& operator*() const { return curr->val; }
                int* operator->() const { return &(curr->val); }
        };

        class constIter {
            private:
                const Node* curr; 
                const Tree* tree;
            public:
                friend class Tree;
                constIter(const Node* node, const Tree* t) : curr(node), tree{t} {}
                constIter(const constIter& other) : curr(other.curr), tree{other.tree} {}

                bool operator==(const constIter& other) const { return tree == other.tree && curr == other.curr; }
                bool operator!=(const constIter& other) const { return !(*this == other); }

               constIter& operator++() {
                    if (curr == tree->NIL) return *this;
                    if (curr->right != tree->NIL) {
                        curr = curr->right;
                        while (curr->left != tree->NIL) curr = curr->left;
                    } else {
                        const Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p;
                    }
                    return *this;
                }

                constIter operator++(int) {
                    constIter tmp(*this);
                    ++(*this);
                    return tmp;
                }

                constIter& operator--() {
                    if (curr == tree->NIL) {
                        curr = tree->getMax(tree->root);
                        return *this;
                    }

                    if (curr->left != tree->NIL) {
                        curr = curr->left;
                        while (curr->right != tree->NIL) curr = curr->right;
                    } else {
                        const Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                constIter operator--(int) {
                    constIter tmp(*this);
                    --(*this);
                    return tmp;
                }

                const int& operator*() const { return curr->val; }
                const int* operator->() const { return &(curr->val); }
        };

        class reverseIter {
            private:
                Node* curr;
                Tree* tree;
            public:
                friend class Tree;
                reverseIter(Node* node, Tree* t) : curr(node), tree{t} {}

                bool operator==(const reverseIter& other) const { return tree == other.tree && curr == other.curr; }
                bool operator!=(const reverseIter& other) const { return !(*this == other); }

                reverseIter& operator++() {
                    if (curr == tree->NIL) {
                        curr = tree->getMax(tree->root);
                        return *this;
                    }

                    if (curr->left != tree->NIL) {
                        curr = curr->left;
                        while (curr->right != tree->NIL) curr = curr->right;
                    } else {
                        Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                reverseIter operator++(int) {
                    reverseIter tmp = *this;
                    ++(*this);
                    return tmp;
                }

                reverseIter& operator--() {
                    if (curr == tree->NIL) return *this;
                    if (curr->right != tree->NIL) {
                        curr = curr->right;
                        while (curr->left != tree->NIL) curr = curr->left;
                    } else {
                        Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p;
                    }
                    return *this;
                }

                reverseIter operator--(int) {
                    reverseIter tmp(*this);
                    --(*this);
                    return tmp;
                }

                int& operator*() const { return curr->val; }
                int* operator->() const { return &(curr->val); }
        };

        class constreverseIter {
            private:
                const Node* curr;
                const Tree* tree;
            public:
                friend class Tree;
                constreverseIter(const Node* node, const Tree* t) : curr(node), tree{t} {}

                bool operator==(const constreverseIter& other) const { return tree == other.tree && curr == other.curr; }
                bool operator!=(const constreverseIter& other) const { return !(*this == other); }

                constreverseIter& operator++() {
                    if (curr == tree->NIL) {
                        curr = tree->getMax(tree->root);
                        return *this;
                    }

                    if (curr->left != tree->NIL) {
                        curr = curr->left;
                        while (curr->right != tree->NIL) curr = curr->right;
                    } else {
                        const Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->left) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p; 
                    }
                    return *this;
                }

                constreverseIter operator++(int) {
                    constreverseIter tmp = *this;
                    ++(*this);
                    return tmp;
                }

                constreverseIter& operator--() {
                    if (curr == tree->NIL) return *this;
                    if (curr->right != tree->NIL) {
                        curr = curr->right;
                        while (curr->left != tree->NIL) curr = curr->left;
                    } else {
                        const Node* p = curr->parent;
                        while (p != tree->NIL && curr == p->right) {
                            curr = p;
                            p = p->parent;
                        }
                        curr = p;
                    }
                    return *this;
                }

                constreverseIter operator--(int) {
                    constreverseIter tmp(*this);
                    --(*this);
                    return tmp;
                }

                const int& operator*() const { return curr->val; }
                const int* operator->() const { return &(curr->val); }
        };

        Iter begin() { return Iter(getMin(root), this); }
        Iter end()   { return Iter(NIL, this); }

        constIter begin() const { return constIter(getMin(root), this); }
        constIter end()   const { return constIter(NIL, this); }

        constIter cbegin() const { return constIter(getMin(root), this); }
        constIter cend()   const { return constIter(NIL, this); }

        reverseIter rbegin() { return reverseIter(NIL, this); }
        constreverseIter rbegin() const { return crbegin(); }
        constreverseIter crbegin() const { return constreverseIter(NIL, this); }

        reverseIter rend() { return reverseIter(getMin(root), this); }
        constreverseIter rend() const { return crend(); }
        constreverseIter crend() const { return constreverseIter(getMin(root), this); }


        Node* root;
        Node* NIL;

        void clear (Node* node);
        void clear();
        Node* copy (Node* node, Node* newParent);
    public:
        Tree();
        Tree(const Tree& other) {root = copy(other.root, NIL); }
        Tree(Tree&& other) : root{std::move(other.root)} {other.root = nullptr; }

        Tree& operator=(const Tree& other);
        Tree& operator=(Tree&& other);

        ~Tree() { clear(root); delete NIL; }

        void rotate_left(Node* x);
        void rotate_right(Node* y);

        void insert(int k);
        void insertFixUp(Node* node);

        Node* search(Node* node, int key);

        Node* getMin(Node* node);
        Node* getMax(Node* node);
        const Node* getMax(const Node* node) const {
            while (node != NIL && node->right != NIL) node = node->right;
            return node;
        }
        const Node* getMin(const Node* node) const {
            while (node != NIL && node->left != NIL) node = node->left;
            return node;
        }

        Node* getPredecessor(Node* node);
        Node* getSuccessor(Node* node);

        void transplant(Node* u, Node* v);
        void remove(int key);
        void deleteNode(Node* z);
        void deleteFixUp(Node* x);

        bool validateBST(Node* root, Node* min, Node* max);
        bool validateRBT();
        int validateBH(Node* root);
};

Tree::Tree() {
    NIL = new Node();
    root = NIL;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    NIL->color = Color::Black;
}

void Tree::clear(Node* node) {
    if (node != NIL) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void Tree::clear() {
    clear(root);
    root = NIL;
}

Tree::Node* Tree::copy (Node* node, Node* newParent) {
    if (node == NIL) return NIL;

    Node* newNode = new Node(node->val);
    newNode->color = node->color;
    newNode->parent = newParent;

    newNode->left = copy(node->left, newNode);
    newNode->right = copy(node->right, newNode);
            
    return newNode;
}


Tree& Tree::operator=(const Tree& other) {
    if (this != &other) {
        clear(root);
        root = copy(other.root, NIL);
    }
    return *this;
} 

Tree& Tree::operator=(Tree&& other) {
    if (this != &other) {
        clear(root);
        delete NIL;
        root = std::move(other.root);
        NIL = std::move(other.NIL);
        
        other.NIL = new Node();
        other.NIL->left = other.NIL;
        other.NIL->right = other.NIL;
        other.NIL->parent = other.NIL;
        other.NIL->color = Color::Black;
        other.root = other.NIL;
    }
    return *this;
}

void Tree::rotate_left(Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NIL) y->left->parent = x;
    
    y->parent = x->parent;
    if (y->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void Tree::rotate_right(Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != NIL) x->right->parent = y;
    
    x->parent = y->parent;
    if (x->parent == NIL) root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;
    
    x->right = y;
    y->parent = x;
}

void Tree::insert(int key) {
    Node* z = new Node(key);
    z->left = NIL;
    z->right = NIL;
    z->parent = NIL;

    Node* p = NIL;
    Node* curr = root;

    while (curr != NIL) {
        p = curr;
        if (key < curr->val) curr = curr->left; 
        else if (key > curr->val) curr = curr->right;
        else return;
    }
    
    z->parent = p;
    if (p == NIL) root = z;
    else if (key < p->val) p->left = z;
    else p->right = z;

    insertFixUp(z);
}

void Tree::insertFixUp(Node* z) {
    while (z->parent->color == Color::Red) {
        if (z->parent == z->parent->parent->right) {
            Node* y = z->parent->parent->left;
            if (y->color == Color::Red) {
                y->color = Color::Black;
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;
                z = z->parent->parent;
            } else {
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;

                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(z);
                }
                rotate_left(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->right;
            if (y->color == Color::Red) {
                y->color = Color::Black;
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;
                z = z->parent->parent;
            } else {
                z->parent->color = Color::Black;
                z->parent->parent->color = Color::Red;

                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(z);
                }
                rotate_right(z->parent->parent);
            }   
        }
    }
    root->color = Color::Black;
}

Tree::Node* Tree::search(Node* node, int key) {
    while (node != NIL && node->val != key) {
        if (key < node->val) node = node->left;
        else if (key > node->val) node = node->right;
    }
    return node;
}

Tree::Node* Tree::getMin(Node* node) {
    while (node != NIL && node->left != NIL) node = node->left;
    return node; 
}

Tree::Node* Tree::getMax(Node* node) {
    while (node != NIL && node->right != NIL) node = node->right;
    return node; 
}

Tree::Node* Tree::getPredecessor(Node* node) {
    if (node->left != NIL) return getMax(node->left);

    Node* p = node->parent;

    while (p != NIL && p->left == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

Tree::Node* Tree::getSuccessor(Node* node) {
    if (node->right != NIL) return getMin(node->right);

    Node* p = node->parent;

    while (p != NIL && p->right == node) {
        node = p;
        p = p->parent;
    }
    return p;
}

void Tree::transplant(Node* u, Node* v) {
    if (u->parent == NIL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;

    v->parent = u->parent;
}

void Tree::remove(int key) {
    Node* z = search(root, key);
    if (z != NIL) deleteNode(z);
}

void Tree::deleteNode(Node* z) {
    Node* y = z;
    Node* x = z;
    Color original = z->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = getMin(z->right);
        original = y->color;
        x = y->right;

        if (y->parent != z) {
            transplant(y, y->right);
            y->right = z->right;
            z->right->parent = y;
        }
 
        transplant(z, y);
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (original == Color::Black) deleteFixUp(x);
}

void Tree::deleteFixUp(Node* x) {
    while (x != root && x->color == Color::Black) {
        if (x == x->parent->left) { 
            Node* w = x->parent->right;

            if (w->color == Color::Red) {
                w->color = Color::Black;
                x->parent->color = Color::Red;
                rotate_left(x->parent);
                w = x->parent->right;
            }
            else if (w->right->color == Color::Black && w->left->color == Color::Black) {
                w->color = Color::Red;
                x = x->parent;
            }
            else {
                if (w->right->color == Color::Black) {
                    w->color = Color::Red;
                    w->left->color = Color::Black;
                    rotate_right(w);
                    w = x->parent->right;
                }
                w->color = w->parent->color;
                w->parent->color = Color::Black;
                w->right->color = Color::Black;
                rotate_left(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;

            if (w->color == Color::Red) {
                w->color = Color::Black;
                x->parent->color = Color::Red;
                rotate_right(x->parent);
                w = x->parent->left;
            }
            else if (w->right->color == Color::Black && w->left->color == Color::Black) {
                w->color = Color::Red;
                x = x->parent;
            }
            else {
                if (w->left->color == Color::Black) {
                    w->color = Color::Red;
                    w->right->color = Color::Black;
                    rotate_left(w);
                    w = x->parent->left;
                }
                w->color = w->parent->color;
                w->parent->color = Color::Black;
                w->left->color = Color::Black;
                rotate_right(x->parent);
                x = root;
            }
        }
    }
    x->color = Color::Black;
}

bool Tree::validateRBT() {
    if (root->color == Color::Red) return false;
    if (!validateBST(root, NIL, NIL)) return false;
    return validateBH(root) != 0;
}

bool Tree::validateBST(Node* root, Node* min, Node* max) {
    if (root == NIL) return true;

    if (min != NIL && root->val <= min->val) return false;
    if (max != NIL && root->val >= max->val) return false;

    return validateBST(root->left, min, root) && validateBST(root->right, root, max);
}

int Tree::validateBH(Node* root) {
    if (root == NIL) return 1;
    if (root->color == Color::Red && (root->left->color == Color::Red || root->right->color == Color::Red)) return false;
    
    int l = validateBH(root->left);
    if (!l) return 0;

    int r = validateBH(root->right);
    if (!r || l != r) return 0;

    return l + (root->color == Color::Black);
}

#endif
