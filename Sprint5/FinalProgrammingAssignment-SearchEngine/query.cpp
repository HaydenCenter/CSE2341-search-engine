#include "query.h"

Query::Query(IndexInterface*& indexArg)
{
    theIndex = indexArg;
    cout << "Enter Query: ";
    string query;
    cin.ignore();
    getline(cin,query);
    istringstream iss(query);
    string word;
    bool NOT = false;
    while(iss >> word)
    {
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        if(NOT)
        {
            notWords.push_back(word);
        }
        else
        {
            if(word == "not")
                NOT = true;
            else
            {
                queryWords.push_back(word);
            }
        }
    }
    auto start = high_resolution_clock::now();
    if(queryWords.size() == 1 && notWords.size() == 0)
    {
        singleSearch();
    }
    else if(queryWords.size() == 1)
    {
        singleSearch();
        notSearch();
    }
    else if(queryWords.size() > 1 && notWords.size() == 0)
    {
        if(queryWords[0] == "and")
        {
            andSearch();
        }
        else if(queryWords[0] == "or")
        {
            orSearch();
        }
        else
        {
            cout << "Invalid Query" << endl;
        }
    }
    else if(queryWords.size() > 1)
    {
        if(queryWords[0] == "and")
        {
            andSearch();
            notSearch();
        }
        else if(queryWords[0] == "or")
        {
            orSearch();
            notSearch();
        }
        else
        {
            cout << "Invalid Query" << endl;
        }
    }
    else
    {
        cout << "Invalid Query" << endl;
    }
    for(map<string,double>::iterator iter = relevancyMap.begin(); iter != relevancyMap.end(); iter++)
    {
        invertedRelevancyMap.emplace(make_pair(iter->second,iter->first));
    }
    int count = 0;
    for(map<double,string>::reverse_iterator iter = invertedRelevancyMap.rbegin(); iter != invertedRelevancyMap.rend() && count < 15; iter++)
    {
        relevantFiles.push_back(iter->second);
        count++;
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Runtime: " << duration.count()/1000000.0 << " seconds" << endl;
}

void Query::singleSearch()
{
    vector<pair<string,double>> tfidf;
    Word w(queryWords[0]);
    Word* wordPtr = theIndex->search(w);
    if(wordPtr == nullptr)
        cout << endl << "Word \"" << queryWords[0] << "\" Not Found In Index";
    else
        tfidf = wordPtr->relevantDocuments(theIndex->getNumDocsParsed());
    for(vector<pair<string,double>>::iterator iter = tfidf.begin(); iter != tfidf.end(); iter++)
        relevancyMap[iter->first] += iter->second;
}

void Query::andSearch()
{
    for(unsigned int i = 1; i < queryWords.size(); i++)
    {
        set<string> temp;
        vector<pair<string,double>> tfidf;
        Word w(queryWords[i]);
        Word* wordPtr = theIndex->search(w);
        if(wordPtr == nullptr)
            cout << endl <<"Word \"" << queryWords[i] << "\" not found in the index";
        else
        {
            tfidf = wordPtr->relevantDocuments(theIndex->getNumDocsParsed());
        }
        for(unsigned int j = 0; j < tfidf.size(); j++)
        {
            temp.insert(tfidf[j].first);
            relevancyMap[tfidf[j].first] += tfidf[j].second;
        }
        querySets.push_back(temp);
    }
    vector<string> result(querySets[0].begin(),querySets[0].end());
    vector<string>::iterator it;
    for(unsigned int i = 1; i < querySets.size(); i++)
    {
        if(querySets[i].size() == 0)
            result.clear();
        if(result.size() != 0)
        {
            it = set_intersection(result.begin(),result.end(),querySets[i].begin(),querySets[i].end(),result.begin());
            result.resize(it - result.begin());
        }
    }
    for(map<string,double>::iterator iter = relevancyMap.begin(); iter != relevancyMap.end(); iter++)
        if(find(result.begin(),result.end(),iter->first) == result.end())
            relevancyMap.erase(iter);
}

void Query::orSearch()
{
    for(unsigned int i = 1; i < queryWords.size(); i++)
    {
        vector<pair<string,double>> tfidf;
        Word w(queryWords[i]);
        Word* wordPtr = theIndex->search(w);
        if(wordPtr == nullptr)
            cout << endl << "Word \"" << queryWords[i] << "\" not found in the index";
        else
        {
            tfidf = wordPtr->relevantDocuments(theIndex->getNumDocsParsed());
        }
        for(vector<pair<string,double>>::iterator iter = tfidf.begin(); iter != tfidf.end(); iter++)
        {
            relevancyMap[iter->first] += iter->second;
        }
    }
}

void Query::notSearch()
{
    for(unsigned int i = 0; i < notWords.size(); i++)
    {
        set<string> temp;
        vector<pair<string,double>> tfidf;
        Word w(notWords[i]);
        Word* wordPtr = theIndex->search(w);
        if(wordPtr == nullptr)
            cout << "Word " << notWords[i] << " not found in the index" << endl;
        else
        {
            tfidf = wordPtr->relevantDocuments(theIndex->getNumDocsParsed());
        }
        for(unsigned int j = 0; j < tfidf.size(); j++)
        {
            temp.insert(tfidf[j].first);
            relevancyMap[tfidf[j].first] += tfidf[j].second;
        }
        notSets.push_back(temp);
    }
    for(unsigned int i = 0; i < notSets.size(); i++)
    {
        for(set<string>::iterator iter = notSets[i].begin(); iter != notSets[i].end(); iter++)
        {
            relevancyMap.erase(*iter);
        }
    }
}

vector<string> Query::getRelevantFiles()
{
    return relevantFiles;
}
