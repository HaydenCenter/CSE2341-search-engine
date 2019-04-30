#ifndef AVLTREE_H
#define AVLTREE_H
#include "avlnode.h"
#include <stdexcept>
#include "indexinterface.h"

using namespace std;

template<class T>
class AvlTree : public IndexInterface
{
    public:
        AvlTree();
        ~AvlTree();
        int& getSize();
        int& getNumDocsParsed();
        int& getAverageWordsPerFile();
        const T& findMin() const;
        const T& findMax() const;
        bool contains(T&);
        bool isEmpty() const;
        void makeEmpty();
        T* insert(T&);
        T* search(T);
        int count();
        void print();
        void output(ofstream&);
    private:
        AvlNode<T>* root;
        int size;
        int numDocsParsed;
        int averageWordsPerFile;
        int height(AvlNode<T>*) const;
        int max(int,int) const;
        AvlNode<T>* findMin(AvlNode<T>*);
        AvlNode<T>* findMax(AvlNode<T>*);
        bool contains(const T&, AvlNode<T>*) const;
        void makeEmpty(AvlNode<T>*&);
        T* insert(const T&, AvlNode<T>*&);
        T* search(T,AvlNode<T>*);
        int count(AvlNode<T>*);
        void print(AvlNode<T>*);
        void output(AvlNode<T>*,ofstream&);
        void rotateWithLeftChild(AvlNode<T>*&);
        void rotateWithRightChild(AvlNode<T>*&);
        void doubleWithLeftChild(AvlNode<T>*&);
        void doubleWithRightChild(AvlNode<T>*&);
};

template<class T>
AvlTree<T>::AvlTree()
{
    root = nullptr;
    size = 0;
    numDocsParsed = 0;
}

template<class T>
AvlTree<T>::~AvlTree()
{
    makeEmpty();
}

template<class T>
int& AvlTree<T>::getSize()
{
    return size;
}

template<class T>
int& AvlTree<T>::getNumDocsParsed()
{
    return numDocsParsed;
}

template<class T>
int& AvlTree<T>::getAverageWordsPerFile()
{
    return averageWordsPerFile;
}

template<class T>
const T& AvlTree<T>::findMin() const
{
    if(isEmpty())
        throw underflow_error("AvlTree is empty");
    return findMin(root)->element;
}

template<class T>
const T& AvlTree<T>::findMax() const
{
    if(isEmpty())
        throw underflow_error("AvlTree is empty");
    return findMax(root)->element;
}

template<class T>
bool AvlTree<T>::contains(T& x)
{
    return contains(x,root);
}

template<class T>
bool AvlTree<T>::isEmpty() const
{
    return root == nullptr;
}

template<class T>
void AvlTree<T>::makeEmpty()
{
    cout << "Emptying Index...";
    makeEmpty(root);
    root = nullptr;
    size = 0;
    numDocsParsed = 0;
    cout << "Index Emptied" << endl;
}

template<class T>
T* AvlTree<T>::insert(T &x)
{
    return insert(x,root);
}

template<class T>
T* AvlTree<T>::search(T value)
{
    return search(value,root);
}

template<class T>
int AvlTree<T>::count()
{
    return count(root);
}

template<class T>
void AvlTree<T>::print()
{
    return print(root);
}

template<class T>
void AvlTree<T>::output(ofstream& outFile)
{
    return output(root,outFile);
}

template<class T>
int AvlTree<T>::height(AvlNode<T>* t) const
{
    return t == nullptr ? -1 : t->height;
}

template<class T>
int AvlTree<T>::max(int lhs, int rhs) const
{
    return lhs > rhs ? lhs : rhs;
}

template<class T>
AvlNode<T>* AvlTree<T>::findMin(AvlNode<T>* nodePtr)
{
    while(nodePtr->left != nullptr)
        nodePtr = nodePtr->left;
    return nodePtr;
}

template<class T>
AvlNode<T>* AvlTree<T>::findMax(AvlNode<T>* nodePtr)
{
    while(nodePtr->right != nullptr)
        nodePtr = nodePtr->right;
    return nodePtr;
}

template<class T>
bool AvlTree<T>::contains(const T& value, AvlNode<T>* nodePtr) const
{
    if(value > nodePtr->element) {
        if(nodePtr->right == nullptr)
            return false;
        return contains(value,nodePtr->right);
    }
    else if(value < nodePtr->element) {
        if(nodePtr->left == nullptr)
            return false;
        return contains(value,nodePtr->left);
    }
    else
        return true;
}

template<class T>
void AvlTree<T>::makeEmpty(AvlNode<T>*& nodePtr)
{
    if(nodePtr)
    {
        makeEmpty(nodePtr->right);
        makeEmpty(nodePtr->left);
        delete nodePtr;
    }
}

template<class T>
T* AvlTree<T>::insert(const T& x, AvlNode<T>*& t)
{
    T* result = nullptr;
    if(t == nullptr) {
        t = new AvlNode<T>(x,nullptr,nullptr);
        size++;
        result = &(t->element);
    }
    else if(x < t->element) {
        result = insert(x,t->left);
        if(height(t->left) - height(t->right) == 2) {
            if(x < t->left->element)
                rotateWithLeftChild(t); //Case1
            else
                doubleWithLeftChild(t); //Case2
        }
    }
    else if(t->element < x) {
        result = insert(x,t->right);
        if(height(t->right) - height(t->left) == 2) {
            if(t->right->element < x)
                rotateWithRightChild(t); //Case4
            else
                doubleWithRightChild(t); //Case3
        }
    }
    else
        result = &(t->element);
    t->height = max(height(t->left), height(t->right)) + 1;
    return result;
}

template<class T>
T* AvlTree<T>::search(T value, AvlNode<T>* nodePtr)
{
    if(isEmpty())
        return nullptr;
    else if(nodePtr == nullptr)
        return nullptr;
    else if(value == nodePtr->element)
        return &nodePtr->element;
    else if(value > nodePtr->element)
        return search(value,nodePtr->right);
    else if(value < nodePtr->element)
        return search(value,nodePtr->left);
    else
        return nullptr;
}

template<class T>
int AvlTree<T>::count(AvlNode<T>* nodePtr)
{
    int result = 0;
    if(nodePtr)
    {
        result += count(nodePtr->left);
        result += count(nodePtr->right);
        result += 1;
    }
    return result;
}

template<class T>
void AvlTree<T>::print(AvlNode<T>* nodePtr)
{
    if(nodePtr) {
        print(nodePtr->left);
        cout << nodePtr->element;
        cout << endl;
        print(nodePtr->right);
    }
}

template<class T>
void AvlTree<T>::output(AvlNode<T>* nodePtr, ofstream& outFile)
{
    if(nodePtr) {
        output(nodePtr->left,outFile);
        outFile << nodePtr->element;
        outFile << endl;
        output(nodePtr->right,outFile);
    }
}

template<class T>
void AvlTree<T>::rotateWithLeftChild(AvlNode<T>*& k2)
{
    AvlNode<T>* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left),height(k2->right)) + 1;
    k1->height = max(height(k1->left),height(k1->right)) + 1;
    k2 = k1;
}

template<class T>
void AvlTree<T>::rotateWithRightChild(AvlNode<T>*& k1)
{
    AvlNode<T>* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left),height(k1->right)) + 1;
    k2->height = max(height(k2->left),height(k2->right)) + 1;
    k1 = k2;
}

template<class T>
void AvlTree<T>::doubleWithLeftChild(AvlNode<T>*& k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template<class T>
void AvlTree<T>::doubleWithRightChild(AvlNode<T>*& k1)
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

#endif // AVLTREE_H
