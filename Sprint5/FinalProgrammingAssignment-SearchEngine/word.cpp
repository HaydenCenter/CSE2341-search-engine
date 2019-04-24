#include "word.h"

Word::Word()
{
    wordText = "";
}

Word::Word(string s)
{
    wordText = s;
}

Word::Word(string s, map<string, int> m)
{
    wordText = s;
    freqMap = m;
}

bool Word::operator==(const Word rhs) const
{
    return wordText == rhs.wordText;
}

bool Word::operator<(const Word rhs) const
{
    return wordText < rhs.wordText;
}

bool Word::operator>(const Word rhs) const
{
    return wordText > rhs.wordText;
}

string &Word::getWordText()
{
    return wordText;
}

map<string, int>& Word::getMap()
{
    return freqMap;
}

void Word::setWordText(string s)
{
    wordText = s;
}

void Word::setMap(map<string,int> mapToSet)
{
    freqMap = mapToSet;
}

vector<pair<double,string>> Word::relevantDocuments(int numDocsParsed)
{

    vector<pair<double,string>> result;
    for(map<string,int>::iterator iter = freqMap.begin(); iter != freqMap.end(); iter++)
    {
        double TF = iter->second / 8832.14;
        double IDF = log((1.0 * numDocsParsed)/freqMap.size());
        double TFIDF = TF * IDF;
        result.push_back(make_pair(TFIDF,iter->first));
    }
    sort(result.begin(),result.end());
    return result;
}
