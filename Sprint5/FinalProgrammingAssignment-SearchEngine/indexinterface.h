#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

template <class V>
class IndexInterface
{
public:
    IndexInterface() {}
    virtual ~IndexInterface() {}
    virtual int getSize() = 0;
    virtual void insert(const V&) = 0;
    virtual void makeEmpty() = 0;
    virtual bool isEmpty() const = 0;
    virtual bool contains(const V&) const = 0;
    virtual V search(V) = 0;
    virtual void print() = 0;
    virtual int count() = 0;
};

#endif // INDEXINTERFACE_H
