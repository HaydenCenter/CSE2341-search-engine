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
    void parse(IndexInterface<Word>*&);
    void saveIndex(IndexInterface<Word>*&);
    void loadIndex(IndexInterface<Word>*&);
    void PrintDemoInfo(IndexInterface<Word>*&,char*);
private:
    vector<string> files;
    set<string> stopwords;
    int numDocumentsParsed;
    int numWordsInIndex;
};

#endif // DOCUMENTHANDLER_H
