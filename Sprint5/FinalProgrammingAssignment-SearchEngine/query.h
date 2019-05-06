#ifndef QUERY_H
#define QUERY_H
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <chrono>
#include "indexinterface.h"
#include "word.h"
#include "searchresulthandler.h"

using namespace std::chrono;

class Query
{
public:
    Query(IndexInterface*&);
    vector<string> getRelevantFiles();
private:
    IndexInterface* theIndex;
    vector<string> queryWords;
    vector<string> notWords;
    vector<string> relevantFiles;
    map<string,double> relevancyMap;
    map<double,string> invertedRelevancyMap;
    vector<set<string>> querySets;
    vector<set<string>> notSets;
    void singleSearch();
    void andSearch();
    void orSearch();
    void notSearch();
};

#endif // QUERY_H
