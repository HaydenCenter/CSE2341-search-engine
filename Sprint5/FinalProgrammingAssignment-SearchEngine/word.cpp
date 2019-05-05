#include "word.h"

Word::Word()
{
    wordText = "";
}

Word::Word(string s)
{
    wordText = s;
}

Word::Word(string s, map<string,pair<int,double>> m)
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

ostream& operator<<(ostream& COUT, const Word& word)
{
    COUT << word.wordText << " ";
    for(auto iter = word.freqMap.begin(); iter != word.freqMap.end(); iter++) {
        COUT << iter->first << " " << iter->second.first << " " << iter->second.second << " ";
    }
    return COUT;
}

string &Word::getWordText()
{
    return wordText;
}

map<string,pair<int,double>>& Word::getMap()
{
    return freqMap;
}

void Word::setWordText(string s)
{
    wordText = s;
}

void Word::setMap(map<string,pair<int,double>> mapToSet)
{
    freqMap = mapToSet;
}

vector<pair<string,double>> Word::relevantDocuments(int numDocsParsed)
{
    vector<pair<string,double>> result;
    for(map<string,pair<int,double>>::iterator iter = freqMap.begin(); iter != freqMap.end(); iter++)
    {
        double TF = iter->second.first / iter->second.second;
        double IDF = log((1.0 * numDocsParsed)/freqMap.size());
        double TFIDF = TF * IDF;
        string f = iter->first;
        double s = TFIDF;
        auto p = make_pair(f,s);
        result.push_back(p);
    }
    return result;
}

int Word::getTotalFrequency()
{
    int result = 0;
    for(map<string,pair<int,double>>::iterator iter = freqMap.begin(); iter != freqMap.end(); iter++)
    {
        result += iter->second.first;
    }
    return result;
}
