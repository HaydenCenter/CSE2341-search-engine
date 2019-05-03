#include "searchresulthandler.h"

SearchResultHandler::SearchResultHandler(vector<string> filesToSet)
{
    fileNames = filesToSet;
    displaySearchResults();

    cout << "Please indicate which file you would like to open by typing full file name & path: ";
    while(true) {
        string fileToOpen;
        cin >> fileToOpen;
        cout << endl;
        bool isPresent = false;
        for(int i = 0; i < fileNames.size(); i++) {
            if(fileToOpen == fileNames.at(i))
                isPresent = true;
        }

        if(isPresent) {
            openFileInfo(fileToOpen);
            break;
        }
        else {
            cout << "Please enter an acceptable file name: ";
        }
    }
}

void SearchResultHandler::displaySearchResults() {
    cout << "Search Results:" << endl;
    for(int i = 0; i < fileNames.size(); i ++) {
        json j;
        ifstream inFS;
        inFS.open(fileNames.at(i));
        if(!inFS.is_open())
            throw exception();
        inFS >> j;
        inFS.close();

        string s = j["absolute_url"];
        istringstream iss(s);
        string caseName;

        for(int i = 0; i < 4; i++) {
            getline(iss, caseName, '/');
        }

        cout << fileNames.at(i) << ": " << caseName << endl;
    }
}

void SearchResultHandler::openFileInfo(string fileToOpen) {
    json j;
    ifstream inFS;
    inFS.open(fileToOpen);
    if(!inFS.is_open())
        throw exception();
    inFS >> j;
    inFS.close();

    string docText = j["plain_text"];
    if(docText == "")
        docText = j["html"];

    for(int i = 0; i < 300; i++) {
        cout << docText.at(i);
    }
    cout << endl;
}
