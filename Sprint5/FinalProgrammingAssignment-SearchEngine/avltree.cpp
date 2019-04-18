/*#include "avltree.h"

template <class T>
AvlTree::AvlTree()
{
    root = nullptr;
}

template <class T>
AvlTree::~AvlTree() {
    makeEmpty();
}

template <class T>
const T& AvlTree::findMin() const {
    if(isEmpty())
        throw UnderflowException();
    return findMin(root)->element;
}

template <class T>
const T& AvlTree::findMax() const {
    if(isEmpty())
        throw UnderflowException();
    return findMax(root)->element;
}

template <class T>
bool AvlTree::contains(const T& x) const {
    return contains(x,root);
}

template <class T>
bool AvlTree::isEmpty() const {
    return root == nullptr;
}

template <class T>
void AvlTree::makeEmpty() {
    makeEmpty(root);
}

template <class T>
void AvlTree::insert(const T& x) {
    insert(x,root);
}

template <class T>
int AvlTree::height(AvlNode* t) const {
    return t == nullptr ? -1 : t->height;
}

template <class T>
T AvlTree::max(T lhs, T rhs) const {
    return lhs > rhs ? lhs : rhs;
}

template <class T>
AvlNode* AvlTree::findMin(AvlNode* nodePtr) {
    while(nodePtr->left != nullptr)
        nodePtr = nodePtr->left;
    return nodePtr;
}

template <class T>
AvlNode* AvlTree::findMax(AvlNode* nodePtr) {
    while(nodePtr->right != nullptr)
        nodePtr = nodePtr->right;
    return nodePtr;
}

template <class T>
bool AvlTree::contains(const T& value, AvlNode* nodePtr) {
    if(value > nodePtr->element) {
        if(nodePtr->right == nullptr)
            return false;
        contains(value,nodePtr->right);
    }
    else if(value < nodePtr->element) {
        if(nodePtr->left == nullptr)
            return false;
        contains(value,nodePtr->left);
    }
    else if(value == nodePtr->element)
        return true;
}

template <class T>
void AvlTree::makeEmpty(AvlNode*& nodePtr) {
    //add code
}

template <class T>
void AvlTree::insert(const T& x, AvlNode *& t) {
    if(t == nullptr)
        t = new AvlNode(x,nullptr,nullptr);
    else if(x < t->element) {
        insert(x,t->left);
        if(height(t->left) - height(t->right) == 2) {
            if(x < t->left->element)
                rotateWithLeftChild(t); //Case1
            else
                doubleWithLeftChild(t); //Case2
        }
    }
    else if(t->element < x) {
        insert(x,t->right);
        if(height(t->right) - height(t->left) == 2) {
            if(t->right->element < x)
                rotateWithRightChild(t); //Case4
            else
                doubleWithRightChild(t); //Case3
        }
    }
    else;
    t->height = max(height(t->left), height(t->right)) + 1;
}

template <class T>
void AvlTree::rotateWithLeftChild(AvlNode*& k2) {
    AvlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left),height(k2->right)) + 1;
    k1->height = max(height(k1->left),height(k1->right)) + 1;
    k2 = k1;
}

template <class T>
void AvlTree::rotateWithRightChild(AvlNode*& k1) {
    AvlNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left),height(k1->right)) + 1;
    k2->height = max(height(k2->left),height(k2->right)) + 1;
    k1 = k2;
}

template <class T>
void AvlTree::doubleWithLeftChild(AvlNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class T>
void AvlTree::doubleWithRightChild(AvlNode*& k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}
*/
