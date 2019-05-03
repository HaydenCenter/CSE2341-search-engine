
#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H
#include <fstream>
#include "word.h"

using namespace std;

class IndexInterface
{
    public:
        IndexInterface() {}
        virtual ~IndexInterface() {}
        virtual int& getSize() = 0;
        virtual int& getNumDocsParsed() = 0;
        virtual double& getAverageWordsPerFile() = 0;
        virtual Word* insert(Word&) = 0;
        virtual void makeEmpty() = 0;
        virtual bool isEmpty() const = 0;
        virtual bool contains(Word&) = 0;
        virtual Word* search(Word) = 0;
        virtual void print() = 0;
        virtual void output(ofstream&) = 0;
};

#endif // INDEXINTERFACE_H
