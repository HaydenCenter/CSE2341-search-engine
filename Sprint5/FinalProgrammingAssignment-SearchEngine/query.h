#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <sstream>
#include "indexinterface.h"
#include "word.h"

using namespace std;

class Query
{
public:
    Query(IndexInterface*&);
private:
    vector<string> queryWords;
    vector<string> notWords;
    vector<string> relevantFiles;
};

#endif // QUERY_H
