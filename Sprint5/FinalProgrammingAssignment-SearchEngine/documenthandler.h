#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H
#include <iostream>
#include <vector>
#include <dirent.h>
#include <cstring>
using namespace std;

class DocumentHandler
{
public:
    DocumentHandler();
    void CreateFilesVector(char*);
private:
    vector<string> files;
};

#endif // DOCUMENTHANDLER_H
