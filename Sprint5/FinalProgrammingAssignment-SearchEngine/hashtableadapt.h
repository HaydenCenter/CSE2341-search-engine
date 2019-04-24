#ifndef HASHTABLEADAPT_H
#define HASHTABLEADAPT_H
#include "indexinterface.h"
#include "hashtable.h"

class HashtableAdapt: public IndexInterface
{
public:
    HashtableAdapt();
    ~HashtableAdapt();
    int& getSize();
    int& getNumDocsParsed();
    Word* insert(Word&);
    void makeEmpty();
    bool isEmpty() const;
    bool contains(Word&);
    Word* search(Word);
    void print();
    void output(ofstream&);
private:
    Hashtable<string,Word> theIndex;
    int numDocsParsed;
};

#endif // HASHTABLEADAPT_H