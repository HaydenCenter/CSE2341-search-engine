#ifndef SEARCHRESULTHANDLER_H
#define SEARCHRESULTHANDLER_H
#include <vector>
#include <iostream>
#include <json.hpp>
#include <fstream>
#include <sstream>
#include <cctype>

using json = nlohmann::json;
using namespace std;


class SearchResultHandler
{
public:
    SearchResultHandler(vector<string>);
    void displaySearchResults();
    bool openFileInfo(int);
private:
    vector<string> fileNames;

};

#endif // SEARCHRESULTHANDLER_H
