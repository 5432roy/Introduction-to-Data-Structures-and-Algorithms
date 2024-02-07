/**
 * Shang-Yu Chan
 * schan88
 * 2023 Fall CSE101 PA7
 * Dictionary.cpp
 * Implementation of the Dictionary using Tree ADT
*/
#include"Dictionary.h"

using namespace std;

/* Exported types */
typedef std::string keyType;
typedef int valType;

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

    s += R->key + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if(R == nil || R->key == N->key) {
        return;
    }

    setValue(R->key, R->val);
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


/* Class Constructors & Destructors */

Dictionary::Node::Node(keyType key, valType val) {
    this->key = key;
    this->val = val;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary() {
    nil = new Node("", -1);
    root = nil;
    current = root;
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


/* Access Functions */

int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    Node* node = search(root, k);
    if(node == nil) {
        throw logic_error("Dictionary: getValue(): key " + k + " does not exist");
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

void Dictionary::setValue(keyType k, valType v) {
    Node* runner = root, * parenet_node = nil;
    while (runner != nil) {
        parenet_node = runner;
        if(k == runner->key) {
            runner->val = v;
            return;
        }
        if (k < runner->key) {
            runner = runner->left;
        } else if (k > runner->key) {
            runner = runner->right;
        }
    }

    Node* newNode = new Node(k, v);
    newNode->parent = parenet_node;
    newNode->left = nil;
    newNode->right = nil;

    if (parenet_node == nil) {
        root = newNode;
    } else if (k < parenet_node->key) {
        parenet_node->left = newNode;
    } else {
        parenet_node->right = newNode;
    }

    num_pairs++;
}

void Dictionary::remove(keyType k) {
    Node* node = search(root, k);
    if(node == nil) {
        throw logic_error("Dictionary: remove(): key " + k + " does not exist");
    }
    
    if (node == current){
        current = nil;
    }

    num_pairs -= 1;
    
    if (node->left == nil){
        if (node->parent == nil){
            root = node->right;
        }
        else if (node == node->parent->left){
            node->parent->left = node->right;
        }
        else {
            node->parent->right = node->right;
        }
        if (node->right != nil){
            node->right->parent = node->parent;
        }
    }
    else if (node->right == nil){
        if (node->parent == nil){
            root = node->left;
        }
        else if (node == node->parent->left){
            node->parent->left = node->left;
        }
        else {
            node->parent->right = node->left;
        }
        if (node->left != nil){
            node->left->parent = node->parent;
        }
        
    }
    else{
        Node* child = findMin(node->right);
        if (child->parent != node){
            if (child->parent == nil){
                root = child->right;
            }
            else if (child == child->parent->left){
                child->parent->left = child->right;
            }
            else {
                child->parent->right = child->right;
            }
            if (child->right != nil){
                child->right->parent = child->parent;
            }
            child->right = node->right;
            child->right->parent = child;
        }
        if (node->parent == nil){
            root = child;
        }
        else if (node == node->parent->left){
            node->parent->left = child;
        }
        else {
            node->parent->right = child;
        }
        if (child != nil){
            child->parent = node->parent;
        }
        child->left = node->left;
        child->left->parent = child;
    }

    delete node;
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