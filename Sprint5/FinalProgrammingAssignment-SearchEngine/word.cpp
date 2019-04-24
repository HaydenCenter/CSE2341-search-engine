#include "word.h"

Word::Word()
{
    wordText = "";
}

Word::Word(string s)
{
    wordText = s;
}

Word::Word(string s, map<string,double> m)
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

map<string,double>& Word::getMap()
{
    return freqMap;
}

void Word::setWordText(string s)
{
    wordText = s;
}

void Word::setMap(map<string,double> mapToSet)
{
    freqMap = mapToSet;
}

vector<pair<double,string>> Word::relevantDocuments(int numDocsParsed)
{

    vector<pair<double,string>> result;
    for(map<string,double>::iterator iter = freqMap.begin(); iter != freqMap.end(); iter++)
    {
        double TF = iter->second;
        double IDF = log((1.0 * numDocsParsed)/freqMap.size());
        double TFIDF = TF * IDF;
        result.push_back(make_pair(TFIDF,iter->first));
    }
    sort(result.begin(),result.end());
    reverse(result.begin(),result.end());
    return result;
}
