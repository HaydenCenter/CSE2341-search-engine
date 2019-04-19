#include "documenthandler.h"

DocumentHandler::DocumentHandler()
{
    ifstream inFile;
    inFile.open("../stopwords.txt");
    if(!inFile.is_open())
    {
        throw exception();
    }
    string temp;
    while(!inFile.eof())
    {
        inFile >> temp;
        stopwords.emplace(temp);
    }

}

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
        {
            throw exception();
        }

        //Stores entire file into json object
        inFile >> j;
        inFile.close();

        //Stores document ID to emplace into map
        int id = j["id"];

        //Parses file as plain text or html if plain text is empty
        string str = j["plain_text"];
        if(str == "")
            str = j["html"];

        //Stems word
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

void DocumentHandler::save()
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

void DocumentHandler::load()
{
    ifstream inFile;
    inFile.open("savedIndex");
    wordMap.clear();
    string buffer;
    getline(inFile,buffer);
    while(!inFile.eof())
    {
        istringstream iss(buffer);
        string temp;
        iss >> temp;
        map<int,int> tempMap;
        wordMap.emplace(temp,tempMap);
        while(!iss.eof())
        {
            int page;
            int freq;
            iss >> page;
            iss >> freq;
            wordMap.find(temp)->second.emplace(page,freq);
        }
        getline(inFile,buffer);
    }
}
