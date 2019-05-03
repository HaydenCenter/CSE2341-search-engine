#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H
#include <iostream>
#include <set>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <string>
#include <json.hpp>
#include "porter2_stemmer.h"
#include "indexinterface.h"
#include "word.h"
using json = nlohmann::json;
using namespace std;

class DocumentHandler
{
public:
    DocumentHandler();
    void getStopwords();
    void getFiles(char*);
    void parse(IndexInterface*&,char*);
    void saveIndex(IndexInterface*&);
    void loadIndex(IndexInterface*&);
    void printStatistics(IndexInterface*&);
    void setAverage(IndexInterface*&);
    void clearStatistics();
private:
    vector<string> files;
    set<string> stopwords;
    vector<double> wordsPerFile;
    double totalNumberOfWordsIndexed;
};

#endif // DOCUMENTHANDLER_H
