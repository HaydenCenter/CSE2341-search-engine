#include "documenthandler.h"

DocumentHandler::DocumentHandler()
{
    ReadInStopWords();
}

//Function to read in stop words and save them to a set
void DocumentHandler::ReadInStopWords() {
    ifstream inFile;
    inFile.open("../stopwords.txt");
    if(!inFile.is_open())
        throw exception();
    string temp;
    while(!inFile.eof())
    {
        inFile >> temp;
        stopwords.emplace(temp);
    }
}

//Function to handle a folder of files and save individual file names in a vector
void DocumentHandler::CreateFilesVector(char* c) {
    string extn = ".json";
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(c)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            int len = strlen(ent->d_name);
            if (ent->d_type == DT_REG &&
                len > extn.length() &&
                strcmp(ent->d_name + len - extn.length(), extn.c_str()) == 0)
                files.push_back(ent->d_name);
        }
        closedir(dir);
    }
    else {
        throw invalid_argument("Provided path could not be opened");
    }
}

//Function to parse all documents and save data into a map
void DocumentHandler::parse()
{
    //Used to parse a small random sample
    srand(time(NULL));
    int x = rand() % 68390;

    //Full Data Set:
  //for(int i = 0; i < files.size(); i++)
    //Random Sample Set:
    for(int i = x; i < x + 100; i++)
    {
        json j;
        ifstream inFile;
        inFile.open("../scotus/" + files[i]);
        if(!inFile.is_open())
            throw exception();

        //Stores entire file into json object
        inFile >> j;

        //Stores document ID to emplace into map
        int id = j["id"];

        //Parses file as plain text or html if plain text is empty
        string str = j["plain_text"];
        if(str == "")
            str = j["html"];

        //Stems word
        istringstream iss(str);
        while(!iss.eof())
        {
            string word;
            iss >> word;
            //cout << word << " -> "; //Remove after done debugging
            Porter2Stemmer::trim(word);
            //cout << word << " -> "; //Remove after done debugging
            Porter2Stemmer::stem(word);
            //cout << word << endl;   //Remove after done debugging

            //Implement insertion to index here
            if(stopwords.find(word) == stopwords.end() && word != "")
            {
                if(wordMap.find(word) == wordMap.end())
                {
                    map<int,int> temp;
                    wordMap.emplace(word,temp);
                }
                map<int,int>* innerMap = &(wordMap.find(word)->second);
                if(innerMap->find(id) == innerMap->end())
                {
                    innerMap->emplace(id,0);
                }
                wordMap.find(word)->second.find(id)->second++;
            }
        }

        cout << endl << files[i] << endl << id << endl << endl;
    }
    for(auto outer = wordMap.begin(); outer != wordMap.end(); outer++)
    {
        cout << outer->first << " = ";
        for(auto inner = outer->second.begin(); inner != outer->second.end(); inner++)
        {
            cout << inner->first;
            if(inner != --outer->second.end())
                cout << ", ";
        }
        cout << endl;
    }
}

//Function to save a copy of the persistant index to disk after parsing
void DocumentHandler::SavePersistantIndex()
{
    ofstream outFile;
    outFile.open("savedIndex");
    for(auto outer = wordMap.begin(); outer != wordMap.end(); outer++)
    {
        outFile << outer->first << " ";
        for(auto inner = outer->second.begin(); inner != outer->second.end(); inner++)
        {
            outFile << inner->first << " " << inner->second << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

//Function to load data from wordmap to the IndexInterface only after parsing
void DocumentHandler::LoadIntoIndexAfterParsing(IndexInterface& theIndex) {
    for(auto i = wordMap.begin(); i != wordMap.end(); i++ ) {
        Word w(i->first, i->second);
        theIndex.insert(w);
    }
}

//Function to load data from saved persistant index to the IndexInterface
void DocumentHandler::LoadIntoIndexFromDisk(IndexInterface& theIndex) {
    ifstream inFile;
    inFile.open("SavedIndex");
    if(!inFile.is_open())
        throw exception();

    string buffer;
    getline(inFile,buffer);
    while(!inFile.eof())
    {
        istringstream iss(buffer);
        string temp;
        iss >> temp;
        map<int,int> tempMap;
        while(!iss.eof())
        {
            int page;
            int freq;
            iss >> page;
            iss >> freq;
            tempMap.emplace(page,freq);
        }
        Word w(temp,tempMap);
        theIndex.insert(w);
        getline(inFile,buffer);
    }
}

