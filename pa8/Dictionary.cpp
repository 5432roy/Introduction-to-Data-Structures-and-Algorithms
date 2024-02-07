/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA8
 * Dictionay.cpp
 * Implmentation of the Red-Black Tree
*/
#include<iostream>
#include"Dictionary.h"


#define RED 0
#define BLACK 1

using namespace std;

/* Helper Functions */

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if(R == nil) {
        return;
    }

    inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    inOrderString(s, R->right);
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if(R == nil) {
        return;
    }

    s += R->key + (R->color == RED ? " (RED)" : "") + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

void Dictionary::BST_insert(Node* M) {
    Node* runner = root, *parent = nil;

    while(runner != nil) {
        parent = runner;
        if(runner->key == M->key) {
            runner->val = M->val;
            return;
        }
        if(runner->key > M->key) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    Node* N = new Node(M->key, M->val);
    N->parent = parent;
    N->left = nil;
    N->right = nil;
    N->color = M->color;

    if (parent == nil) {
        root = N;
    } else if (M->key < parent->key) {
        parent->left = N;
    } else {
        parent->right = N;
    }

    num_pairs++;
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if(R == nil || R->key == N->key) {
        return;
    }

    BST_insert(R);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
}

void Dictionary::postOrderDelete(Node* R) {
    if(R == nil) {
        return;
    }

    postOrderDelete(R->left);
    postOrderDelete(R->right);
    num_pairs -= 1;
    delete R;
    R = nil;
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    while(R != nil && R->key != k) {
        if(R->key > k) {
            R = R->left;
        } else {
            R = R->right;
        }
    }
    return R;
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    if(R == nil) {
        throw logic_error("Dictionary(), findMin(): code logic error");
    }
    if(R->left == nil) {
        return R;
    }
    return findMin(R->left);
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    if(R == nil) {
        throw logic_error("Dictionary(), findMax(): code logic error");
    }
    if(R->right == nil) {
        return R;
    }
    return findMax(R->right);
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N == findMax(root) || N == nil){
        return nil;
    }
    if (N->right != nil){
        return findMin(N->right);
    }
    Node* parent = N->parent;
    while (parent != nil && N == parent->right){
        N = parent;
        parent = parent->parent;
    }
    return parent;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N == findMin(root) || N == nil){
        return nil;
    }
    if (N->left != nil){
        return findMax(N->left);
    }
    Node* parent = N->parent;
    while (parent != nil && N == parent->left){
        N = parent;
        parent = parent->parent;
    }
    return parent;
}

void Dictionary::LeftRotate(Node* N) {
    Node* child = N->right;

    if(child != nil) {
        child->parent = N->parent;
    }
    if(N == root) {
        root = child;
    } else {
        if(N->parent->left == N) {
            N->parent->left = child;
        } else {
            N->parent->right = child;
        }
    }

    N->right = child->left;
    if(child->left != nil) {
        child->left->parent = N;
    }

    child->left = N;
    if(N != nil) {
        N->parent = child;
    }
}

void Dictionary::RightRotate(Node* N) {
    Node* child = N->left;

    if(child != nil) {
        child->parent = N->parent;
    }
    if(N == root) {
        root = child;
    } else {
        if(N->parent->left == N) {
            N->parent->left = child;
        } else {
            N->parent->right = child;
        }
    }

    N->left = child->right;
    if(N->left != nil) {
        N->left->parent = N;
    }

    child->right = N;
    if(N != nil) {
        N->parent = child;
    }
}

void Dictionary::RB_InsertFixUp(Node* N) {
    if(N == nil) {
        return;
    }

    if(N == root) {
        N->color = BLACK;
        return; 
    }

    if(N->parent->color == RED) {
        Node* uncle = N->parent == N->parent->parent->left ? N->parent->parent->right : N->parent->parent->left;
        
        if(uncle->color == RED) {
            N->parent->color = BLACK;
            uncle->color = BLACK;
            N->parent->parent->color = RED;
            RB_InsertFixUp(N->parent->parent);
        } else {
            if(N == N->parent->left) {
                if(uncle == N->parent->parent->right) {
                    N->parent->color = N->parent->parent->color;
                    N->parent->parent->color = RED;
                    RightRotate(N->parent->parent);
                } else {
                    RightRotate(N->parent);
                    RB_InsertFixUp(N->right);
                }
            } else {
                if(uncle == N->parent->parent->left) {
                    N->parent->color = N->parent->parent->color;
                    N->parent->parent->color = RED;
                    LeftRotate(N->parent->parent);
                } else {
                    LeftRotate(N->parent);
                    RB_InsertFixUp(N->left);
                }
            }
        }
    }
}

void Dictionary::RB_Transplant(Node* u, Node* v){
    if (u->parent == nil){
        root = v;
    }
    else if (u == u->parent->left){
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) {
    Node* sibling;
    while (N != root && N->color == BLACK){
        if (N == N->parent->left){
            sibling = N->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;               
                N->parent->color = RED;         
                LeftRotate(N->parent);          
                sibling = N->parent->right;           
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;                 
                N = N->parent;                  
            } else {
                if (sibling->right->color == BLACK){
                    sibling->left->color = BLACK;     
                    sibling->color = RED;             
                    RightRotate(sibling);             
                    sibling = N->parent->right;       
                }
                sibling->color = N->parent->color;    
                N->parent->color = BLACK;       
                sibling->right->color = BLACK;        
                LeftRotate(N->parent);          
                N = root;                       
            }
        }
        else{
            sibling = N->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;               
                N->parent->color = RED;         
                RightRotate(N->parent);         
                sibling = N->parent->left;            
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;                 
                N = N->parent;                  
            } else {
                if (sibling->left->color == BLACK){
                    sibling->right->color = BLACK;    
                    sibling->color = RED;             
                    LeftRotate(sibling);              
                    sibling = N->parent->left;        
                }
                sibling->color = N->parent->color;    
                N->parent->color = BLACK;       
                sibling->left->color = BLACK;         
                RightRotate(N->parent);         
                N = root;                       
            }
        }
    }
    N->color = BLACK;
}

/* Class Constructors & Destructors */

Dictionary::Node::Node(keyType key, valType val) {
    this->key = key;
    this->val = val;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = BLACK;
}

Dictionary::Dictionary() {
    nil = new Node("", -1);
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
    nil = new Node("", -1);
    root = nil;
    current = root;
    num_pairs = 0;

    preOrderCopy(D.root, nil);
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    Node* node = search(root, k);
    if(node == nil) {
        throw logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return node->val;
}

bool Dictionary::hasCurrent() const {
    return current != nil;
}

keyType Dictionary::currentKey() const {
    if(!hasCurrent()) {
        throw logic_error("Dictionary: currentKey(): current undefined");
    }
    return current->key;
}

valType& Dictionary::currentVal() const {
    if(!hasCurrent()) {
        throw logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}


/* Manipulation Procedures */

void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = root;
}

void Dictionary::setValue(keyType key, valType val) {
    Node* runner = root, *parent = nil;

    while(runner != nil) {
        parent = runner;
        if(runner->key == key) {
            runner->val = val;
            return;
        }
        if(runner->key > key) {
            runner = runner->left;
        } else {
            runner = runner->right;
        }
    }

    Node* N = new Node(key, val);
    N->parent = parent;
    N->left = nil;
    N->right = nil;
    N->color = RED;

    if (parent == nil) {
        root = N;
    } else if (key < parent->key) {
        parent->left = N;
    } else {
        parent->right = N;
    }

    RB_InsertFixUp(N);

    num_pairs++;
}

void Dictionary::remove(keyType k) {
    Node* N = search(root, k);
    if(N == nil) {
        throw logic_error("remove(): key \"" + k + "\" does not exist");
    }

    if(current == N) {
        current = nil;
    }

    Node* child;
    int original_color = N->color;

    if (N->left == nil){
        child = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil){
        child = N->left;
        RB_Transplant(N, N->left);
    }
    else{
        Node* replace = findMin(N->right);
        original_color = replace->color;
        child = replace->right;
        if (replace->parent == N){
            child->parent = replace;
        }
        else{
            RB_Transplant(replace, replace->right);
            replace->right = N->right;
            replace->right->parent = replace;
        }
        RB_Transplant(N, replace);
        replace->left = N->left;
        replace->left->parent = replace;
        replace->color = N->color;
    }
    if (original_color == BLACK){
        RB_DeleteFixUp(child);
    }

    num_pairs -= 1;
    delete N;
}

void Dictionary::begin() {
    current = size() == 0 ? nil : findMin(root);
}

void Dictionary::end() {
    current = size() == 0 ? nil : findMax(root);
}

void Dictionary::next() {
    if(!hasCurrent()) {
        throw logic_error("Dictionary: next(): current undefined");
    }
    current = findNext(current);
}

void Dictionary::prev() {
    if(!hasCurrent()) {
        throw logic_error("Dictionary: prev(): current undefined");
    }
    current = findPrev(current);
}


/* Other Functions */

string Dictionary::to_string() const {
    string res = "";
    inOrderString(res, root);
    return res;
}

string Dictionary::pre_string() const {
    string res = "";
    preOrderString(res, root);
    return res;
}

bool Dictionary::equals(const Dictionary& D) const {
    if(size() != D.size()) {
        return false;
    }
    return to_string() == D.to_string();
}


/* Overloaded Operators */

ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D) {
    if (this != &D){
        Dictionary temp = D;
        
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);

        num_pairs = temp.num_pairs;
    }
    return *this;
}
