#include "query.h"

Query::Query(IndexInterface*& theIndex)
{
    cout << "Enter Query: " << endl;
    string query;
    cin.ignore();
    getline(cin,query);
    istringstream iss(query);
    string word;
    bool NOT = false;
    while(iss >> word && !NOT)
    {
        if(word == "NOT")
            NOT = true;
        else
        {
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            queryWords.push_back(word);
        }
    }
    while(iss >> word && NOT)
    {
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        notWords.push_back(word);
    }

//    cout << "Query Words:" << endl;
//    for(int i = 0; i < queryWords.size(); i++)
//        cout << queryWords[i] << endl;
//    cout << endl << "Not Words:" << endl;
//    for(int i = 0; i < notWords.size(); i++)
//        cout << notWords[i] << endl;

    if(queryWords.size() == 1 && notWords.size() == 0)
    {
        map<string,double> tfidf;
        Word w(queryWords[0]);
        Word* wordPtr = theIndex->search(w);
        if(wordPtr == nullptr)
            cout << "Word Not Found In Index" << endl;
        else
            tfidf = wordPtr->relevantDocuments(theIndex->getNumDocsParsed());
        for(map<string,double>::iterator iter = tfidf.begin(); iter != tfidf.end(); iter++)
            relevantFiles.push_back(iter->first);
    }
    else if(queryWords.size() == 1)
    {
        cout << "1 word query with not operator not implemented yet" << endl;
    }
    else if(notWords.size() == 0)
    {
        if(queryWords[0] == "AND")
        {

        }
        if(queryWords[0] == "OR")
        {

        }
        else
        {
            cout << "Invalid Query" << endl;
        }
    }
    else
    {
        if(queryWords[0] == "AND")
        {

        }
        if(queryWords[0] == "OR")
        {

        }
        else
        {
            cout << "Invalid Query" << endl;
        }
    }
    for(int i = 0; i < relevantFiles.size(); i++)
        cout << relevantFiles[i] << endl;
}
