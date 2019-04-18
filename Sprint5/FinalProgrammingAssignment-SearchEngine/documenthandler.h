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
using json = nlohmann::json;
using namespace std;

class DocumentHandler
{
public:
    DocumentHandler();
    void CreateFilesVector(char*);
    void parse();
    void save();
    void load();
private:
    map<string,map<int,int>> wordMap;
    vector<string> files;
    set<string> stopwords;
};

#endif // DOCUMENTHANDLER_H
