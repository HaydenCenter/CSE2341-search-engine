#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <fstream>

using namespace std;

template <class V>
class IndexInterface
{
public:
    IndexInterface() {}
    virtual ~IndexInterface() {};
    virtual int getSize() = 0;
    virtual V* insert(const V&) = 0;
    virtual void makeEmpty() = 0;
    virtual bool isEmpty() const = 0;
    virtual bool contains(const V&) const = 0;
    virtual V* search(V) = 0;
    virtual void print() = 0;
    virtual void output(ofstream&) = 0;
    virtual int count() = 0;
};

#endif // INDEXINTERFACE_H
