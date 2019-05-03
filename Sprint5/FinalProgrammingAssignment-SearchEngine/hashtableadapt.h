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
    double& getAverageWordsPerFile();
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
    double averageWordsPerFile;
};

#endif // HASHTABLEADAPT_H
