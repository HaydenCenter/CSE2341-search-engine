#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include "indexinterface.h"
#include "word.h"

using namespace std;

class Query
{
public:
    Query(IndexInterface*&);
    vector<string> getRelevantFiles();
private:
    vector<string> queryWords;
    vector<string> notWords;
    vector<string> relevantFiles;
    map<string,double> relevancyMap;
    map<double,string> invertedRelevancyMap;
    vector<set<string>> querySets;
};

#endif // QUERY_H
