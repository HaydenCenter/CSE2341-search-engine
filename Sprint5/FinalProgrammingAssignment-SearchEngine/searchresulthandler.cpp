#include "searchresulthandler.h"

SearchResultHandler::SearchResultHandler(vector<string> filesToSet, char* inputFolder)
{
    fileNames = filesToSet;
    displaySearchResults(inputFolder);

    cout << "Please indicate which file you would like to open by typing full file name: ";
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

void SearchResultHandler::displaySearchResults(char* inputFolder) {
    cout << "Search Results:" << endl;
    for(int i = 0; i < fileNames.size(); i ++) {
        json j;
        ifstream inFS;
        inFS.open(inputFolder + fileNames.at(i));
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

}
