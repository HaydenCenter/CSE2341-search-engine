#ifndef AVLTREE_H
#define AVLTREE_H
#include "avlnode.h"
#include <stdexcept>
#include "indexinterface.h"

using namespace std;

template <class T>
class AvlTree : public IndexInterface<T>
{
public:
    AvlTree();
    ~AvlTree();
    const T& findMin() const;
    const T& findMax() const;
    bool contains(const T&) const;
    bool isEmpty() const;
    void makeEmpty();
    void insert(const T&);
    T search(T);
private:
    AvlNode<T>* root;
    int height(AvlNode<T>*) const;
    int max(int,int) const;
    AvlNode<T>* findMin(AvlNode<T>*);
    AvlNode<T>* findMax(AvlNode<T>*);
    bool contains(const T&, AvlNode<T>*) const;
    void makeEmpty(AvlNode<T>*&);
    T search(T,AvlNode<T>*);
    void insert(const T&, AvlNode<T>*&);
    void rotateWithLeftChild(AvlNode<T>*&);
    void rotateWithRightChild(AvlNode<T>*&);
    void doubleWithLeftChild(AvlNode<T>*&);
    void doubleWithRightChild(AvlNode<T>*&);
};

template <class T>
AvlTree<T>::AvlTree()
{
    root = nullptr;
}

template <class T>
AvlTree<T>::~AvlTree() {
    makeEmpty();
}

template <class T>
const T& AvlTree<T>::findMin() const {
    if(isEmpty())
        throw underflow_error("AvlTree is empty");
    return findMin(root)->element;
}

template <class T>
const T& AvlTree<T>::findMax() const {
    if(isEmpty())
        throw underflow_error("AvlTree is empty");
    return findMax(root)->element;
}

template <class T>
bool AvlTree<T>::contains(const T& x) const {
    return contains(x,root);
}

template <class T>
bool AvlTree<T>::isEmpty() const {
    return root == nullptr;
}

template <class T>
void AvlTree<T>::makeEmpty() {
    makeEmpty(root);
    root = nullptr;
}

template <class T>
void AvlTree<T>::insert(const T& x) {
    insert(x,root);
}

template <class T>
T AvlTree<T>::search(T value) {
    return search(value,root);
}

template <class T>
int AvlTree<T>::height(AvlNode<T>* t) const {
    return t == nullptr ? -1 : t->height;
}

template <class T>
int AvlTree<T>::max(int lhs, int rhs) const {
    return lhs > rhs ? lhs : rhs;
}

template <class T>
AvlNode<T>* AvlTree<T>::findMin(AvlNode<T>* nodePtr) {
    while(nodePtr->left != nullptr)
        nodePtr = nodePtr->left;
    return nodePtr;
}

template <class T>
AvlNode<T>* AvlTree<T>::findMax(AvlNode<T>* nodePtr) {
    while(nodePtr->right != nullptr)
        nodePtr = nodePtr->right;
    return nodePtr;
}

template <class T>
bool AvlTree<T>::contains(const T& value, AvlNode<T>* nodePtr) const {
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
void AvlTree<T>::makeEmpty(AvlNode<T>*& nodePtr) {
    if(nodePtr->right != nullptr)
        makeEmpty(nodePtr->right);
    if(nodePtr->left != nullptr)
        makeEmpty(nodePtr->left);
    delete nodePtr;
}

template <class T>
T AvlTree<T>::search(T value, AvlNode<T>* nodePtr) {
    if(isEmpty())
        throw underflow_error("No values to search");
    if(value > nodePtr->element) {
        if(nodePtr->right == nullptr)
            throw invalid_argument("Value is not present in the AvlTree");
        search(value,nodePtr->right);
    }
    else if(value < nodePtr->element) {
        if(nodePtr->left == nullptr)
            throw invalid_argument("Value is not present in the AvlTree");
        search(value,nodePtr->left);
    }
    else if(value == nodePtr->element)
        return nodePtr->element;
}

template <class T>
void AvlTree<T>::insert(const T& x, AvlNode<T>*& t) {
    if(t == nullptr)
        t = new AvlNode<T>(x,nullptr,nullptr);
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
void AvlTree<T>::rotateWithLeftChild(AvlNode<T>*& k2) {
    AvlNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left),height(k2->right)) + 1;
    k1->height = max(height(k1->left),height(k1->right)) + 1;
    k2 = k1;
}

template <class T>
void AvlTree<T>::rotateWithRightChild(AvlNode<T>*& k1) {
    AvlNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left),height(k1->right)) + 1;
    k2->height = max(height(k2->left),height(k2->right)) + 1;
    k1 = k2;
}

template <class T>
void AvlTree<T>::doubleWithLeftChild(AvlNode<T>*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class T>
void AvlTree<T>::doubleWithRightChild(AvlNode<T>*& k1) {
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

#endif // AVLTREE_H
