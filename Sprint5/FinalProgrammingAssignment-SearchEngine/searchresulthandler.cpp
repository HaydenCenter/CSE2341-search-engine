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
            if(caseName[j] == '-')
                caseName[j] = ' ';
            if(caseName[j] == ' ')
                caseName[j + 1] = toupper(caseName[j + 1]);
        }

        cout << "(" << i+1 << ") - " << fileNames.at(i) << ": " << caseName << endl;
    }
}

//Opens a specific file and prints out the first 100 words
bool SearchResultHandler::openFileInfo(int docNum) {
    if(docNum < fileNames.size()) {
        json j;
        ifstream inFS;
        inFS.open(fileNames[docNum]);
        if(!inFS.is_open())
            throw exception();
        inFS >> j;
        inFS.close();

        string docText = j["plain_text"];
        if(docText == "")
            docText = j["html"];

//        for(int i = 0; i < 300; i++) {
//            cout << docText.at(i);
//        }
        int wordCount = 0;
        int charCount = 0;
        int bracketCount = 0;
        while(wordCount < 300)
        {
            if(docText[charCount] == '<')
                bracketCount++;
            if(bracketCount == 0)
                cout << docText[charCount];
            if(docText[charCount] == '>')
                bracketCount--;
            if(docText[charCount] == ' ')
                wordCount++;
            charCount++;
        }
        cout << "..." << endl;
        return true;
    }
    else {
        return false;
    }
}
