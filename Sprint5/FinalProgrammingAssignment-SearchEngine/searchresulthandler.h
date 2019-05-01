#ifndef SEARCHRESULTHANDLER_H
#define SEARCHRESULTHANDLER_H
#include <vector>
#include <iostream>
#include <json.hpp>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using namespace std;


class SearchResultHandler
{
public:
    SearchResultHandler(vector<string>,char*);
    void displaySearchResults(char*);
    void openFileInfo(char*,string);
private:
    vector<string> fileNames;

};

#endif // SEARCHRESULTHANDLER_H
