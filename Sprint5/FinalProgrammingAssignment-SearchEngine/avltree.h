#ifndef AVLTREE_H
#define AVLTREE_H
#include "avlnode.h"
#include <stdexcept>

template <class T>
class AvlTree
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
private:
    AvlNode* root;
    int height(AvlNode*) const;
    T max(T,T);
    AvlNode* findMin(AvlNode*&); //implement
    AvlNode* findMax(AvlNode*&); //implement
    bool contains(const T&, AvlNode*&); //implement
    void makeEmpty(AvlNode*&); //implement
    void insert(const T&, AvlNode*);
    void rotateWithLeftChild(AvlNode*&);
    void rotateWithRightChild(AvlNode*&);
    void doubleWithLeftChild(AvlNode*&);
    void doubleWithRightChild(AvlNode*&);
};

#endif // AVLTREE_H
