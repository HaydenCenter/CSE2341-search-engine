#ifndef AVLNODE_H
#define AVLNODE_H

template <class U>
class AvlNode {
public:
    U element;
    AvlNode* left;
    AvlNode* right;
    int height;

    AvlNode(const U& theElement, AvlNode* lt, AvlNode* rt, int h = 0) {
        element = theElement;
        left = lt;
        right = rt;
        height = h;
    }
}
#endif // AVLNODE_H
