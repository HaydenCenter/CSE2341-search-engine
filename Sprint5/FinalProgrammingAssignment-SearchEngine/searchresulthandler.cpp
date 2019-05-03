#include "searchresulthandler.h"

//Displays top search results and allows user to select a file to view
SearchResultHandler::SearchResultHandler(vector<string> filesToSet)
{
    fileNames = filesToSet;
}

//Displays top 15 results and their court case name
void SearchResultHandler::displaySearchResults() {
    cout << "Search Results:" << endl;
    for(unsigned int i = 0; i < fileNames.size(); i ++) {
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

        caseName[0] = toupper(caseName[0]);
        for(unsigned int j = 1; j < caseName.length(); j++) {
            if(caseName[i] == '-')
                caseName[i] = ' ';
            if(caseName[i] == ' ')
                caseName[i + 1] = toupper(caseName[i + 1]);
        }

        cout << "(" << i+1 << ") - " << fileNames.at(i) << ": " << caseName << endl;
    }
}

//Opens a specific file and prints out the first 100 words
void SearchResultHandler::openFileInfo() {
    cout << "Please indicate which file you would like to open by typing full file name & path: ";
    while(true) {
        string fileToOpen;
        cin >> fileToOpen;
        cout << endl;
        bool isPresent = false;
        for(unsigned int i = 0; i < fileNames.size(); i++) {
            if(fileToOpen == fileNames.at(i))
                isPresent = true;
        }

        if(isPresent) {
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
            break;
        }
        else {
            cout << "Please enter an acceptable file name: ";
        }
    }
}
