#include "documenthandler.h"

using namespace std;

DocumentHandler::DocumentHandler()
{
    getStopwords();
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
void DocumentHandler::parse(IndexInterface*& theIndex, char* inputFolder)
{
    //Used to parse a small random sample
    srand(time(NULL));
    int x = 0;
    //int x = rand() % 68390 - 100;
    int numDocumentsParsed = 0;

    //Full Data Set:
    //for(unsigned int i = 0; i < files.size(); i++)
    //Sample Set:
    for(int i = x; i < x + 1000; i++)
    {
        if(i % 100 == 0)
            cout << i << endl;
        json j;
        ifstream inFile;
        inFile.open(inputFolder + files[i]);
        if(!inFile.is_open())
            throw exception();
        numDocumentsParsed++;
        //Stores entire file into json object
        inFile >> j;
        inFile.close();

        //Stores document ID to emplace into map
        string id = files[i];
        unordered_map<string,int> freqMap;

        //Parses file as plain text or html if plain text is empty
        string str = j["plain_text"];
        if(str == "")
            str = j["html"];

        //Stems word and stores in wordMap
        istringstream iss(str);
        map<string,string> stemMap;
        double numWords = 0.0;
        string word;
        while(iss >> word)
        {
            if(stemMap.count(word) == 0)
            {
                string origWord = word;
                Porter2Stemmer::trim(word);
                Porter2Stemmer::stem(word);
                stemMap.emplace(make_pair(origWord,word));
            }
            else
                word = stemMap.find(word)->second;

            if(stopwords.count(word) == 0 && word != "")
            {
                freqMap[word]++;
                numWords++;
            }
        }
        for(unordered_map<string,int>::iterator iter = freqMap.begin(); iter != freqMap.end(); iter++)
        {
            map<string,double> tempMap;
            Word w(iter->first,tempMap);
            Word* wordPtr = theIndex->insert(w);
            wordPtr->getMap().emplace(make_pair(id,(iter->second/numWords) * 10000));
        }
        wordsPerFile.push_back(numWords);
    }
    cout << endl;
    theIndex->getNumDocsParsed() += numDocumentsParsed;
}

//Function to save a copy of the persistant index to disk after parsing
void DocumentHandler::saveIndex(IndexInterface*& theIndex)
{
    cout << "Saving Index...";
    ofstream outFile;
    outFile.open("savedIndex");
    if(!outFile.is_open())
        throw exception();

    outFile << theIndex->getNumDocsParsed() << endl;
    outFile << theIndex->getSize() << endl;
    theIndex->output(outFile);
    outFile.close();
    cout << "Index Saved" << endl;
}

//Function to load data from saved persistant index to the IndexInterface
void DocumentHandler::loadIndex(IndexInterface*& theIndex)
{
    theIndex->makeEmpty();
    ifstream inFile;
    inFile.open("savedIndex");
    if(!inFile.is_open())
        throw exception();
    int numWordsInIndex;
    inFile >> theIndex->getNumDocsParsed();
    inFile >> numWordsInIndex;
    string buffer;
    getline(inFile,buffer);
    getline(inFile,buffer);
    while(!inFile.eof())
    {
        istringstream iss(buffer);
        string temp;
        iss >> temp;
        map<string,double> tempMap;
        string page;
        while(iss >> page)
        {
            double freq;
            iss >> freq;

            tempMap.emplace(make_pair(page,freq));
        }
        Word w(temp,tempMap);
        theIndex->insert(w);
        getline(inFile,buffer);
    }
    inFile.close();
    if(numWordsInIndex != theIndex->getSize())
        throw exception();
}

//Function to print out information required for Monday's demo
void DocumentHandler::printStatistics(IndexInterface*& theIndex)
{
    cout << "Number of documents parsed: " << theIndex->getNumDocsParsed() << endl;
    cout << "Number of unique words in the index: " << theIndex->getSize() << endl;
    getAverageWordsPerFile(theIndex);
    cout << "Average number of words indexed per opinion: " << theIndex->getAverageWordsPerFile() << endl;
    //include top 50 most frequent words

}

void DocumentHandler::getAverageWordsPerFile(IndexInterface*& theIndex) {
    double average = 0;
    for(unsigned int i = 0; i < wordsPerFile.size(); i++) {
        average = average + wordsPerFile.at(i);
    }
    average = average / wordsPerFile.size();
    theIndex->getAverageWordsPerFile() = average;
}
