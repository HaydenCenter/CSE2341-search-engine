#include "documenthandler.h"

DocumentHandler::DocumentHandler()
{
    //getStopwords();
    stopwords.insert("A");
    numWordsInIndex = 0;
    numDocumentsParsed = 0;
}

//Function to read in stop words and save them to a set
void DocumentHandler::getStopwords()
{
    ifstream inFile;
    inFile.open("../stopwords.txt");
    if(!inFile.is_open())
        throw exception();

    while(!inFile.eof())
    {
        string temp;
        inFile >> temp;
        stopwords.insert(temp);
    }
    inFile.close();
}

//Function to handle a folder of files and save individual file names in a vector
void DocumentHandler::getFiles(char* c)
{
    string extn = ".json";
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(c)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            unsigned int len = strlen(ent->d_name);
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
void DocumentHandler::parse(IndexInterface<Word>*& theIndex)
{
    //Used to parse a small random sample
    srand(time(NULL));
    int x = 0;
    //int x = rand() % 68390 - 100;

    //Full Data Set:
    //for(unsigned int i = 0; i < files.size(); i++)
    //Sample Set:
    for(int i = x; i < x + 100; i++)
    {
        json j;
        ifstream inFile;
        inFile.open("../scotus/" + files[i]);
        if(!inFile.is_open())
            throw exception();
        numDocumentsParsed++;
        //Stores entire file into json object
        inFile >> j;
        inFile.close();

        //Stores document ID to emplace into map
        int id = j["id"];

        //Parses file as plain text or html if plain text is empty
        string str = j["plain_text"];
        if(str == "")
            str = j["html"];

        //Stems word and stores in wordMap
        istringstream iss(str);
        map<string,string> stemMap;
        while(!iss.eof())
        {
            string word;
            iss >> word;

            if(stemMap.find(word) == stemMap.end())
            {
                string origWord = word;
                Porter2Stemmer::trim(word);
                Porter2Stemmer::stem(word);
                stemMap.emplace(origWord,word);
            }
            else
                word = stemMap.find(word)->second;

            //if(stopwords.find(word) == stopwords.end() && word != "")
            //{
                Word* wordPtr = theIndex->search(word);
                if(wordPtr == nullptr)
                {
                    map<int,int> temp;
                    Word w(word,temp);
                    wordPtr = theIndex->insert(w);
                }
                map<int,int>* freqMap = &wordPtr->getMap();
                //map<int,int>* innerMap = &(wordMap.find(word)->second);
                if(freqMap->find(id) == freqMap->end())
                {
                    freqMap->emplace(id,0);
                }
                theIndex->search(word)->getMap().find(id)->second++;
                //wordMap.find(word)->second.find(id)->second++;
            //}
        }
        //Tracks progress
        cout << i << endl;
    }
    cout << "------" << endl;

    //Stores in index
    for(auto i = wordMap.begin(); i != wordMap.end(); i++ ) {
        Word w(i->first, i->second);
        theIndex->insert(w);
        numWordsInIndex++;
    }
    saveIndex(theIndex);
}

//Function to save a copy of the persistant index to disk after parsing
void DocumentHandler::saveIndex(IndexInterface<Word>*& theIndex)
{
    ofstream outFile;
    outFile.open("savedIndex");
    if(!outFile.is_open())
        throw exception();

    outFile << numDocumentsParsed << endl;
    outFile << theIndex->getSize() << endl;
    theIndex->output(outFile);
    outFile.close();
}

//Function to load data from saved persistant index to the IndexInterface
void DocumentHandler::loadIndex(IndexInterface<Word>*& theIndex)
{
    ifstream inFile;
    inFile.open("savedIndex");
    if(!inFile.is_open())
        throw exception();

    inFile >> numDocumentsParsed;
    inFile >> numWordsInIndex;
    string buffer;
    getline(inFile,buffer);
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
        theIndex->insert(w);
        getline(inFile,buffer);
    }
}

//Function to print out information required for Monday's demo
void DocumentHandler::PrintDemoInfo(IndexInterface<Word>*& theIndex, char* word)
{
    cout << "Number of documents parsed: " << numDocumentsParsed << endl;
    cout << "Number of unique words in the index: " << theIndex->getSize() << endl;

    string wordToFind(word);
    Word w(wordToFind);
    Word* searchResult = theIndex->search(w);

    if(searchResult == nullptr)
        cout << "The word " << wordToFind << " is not found within the index" << endl;
    else
        cout << "The word " << searchResult->getWordText() << " is found in " << searchResult->getMap().size() << " documents." << endl;;
}

