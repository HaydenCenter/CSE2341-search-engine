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

ostream& operator<<(ostream& COUT, const Word& word)
{
    COUT << word.wordText << " ";
    for(auto iter = word.freqMap.begin(); iter != word.freqMap.end(); iter++) {
        COUT << iter->first << " " << iter-> second << " ";
    }
    return COUT;
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

map<string,double> Word::relevantDocuments(int numDocsParsed)
{
    for(map<string,double>::iterator iter = freqMap.begin(); iter != freqMap.end(); iter++)
    {
        double TF = iter->second;
        double IDF = log((1.0 * numDocsParsed)/freqMap.size());
        double TFIDF = TF * IDF;
        iter->second = TFIDF;
    }
    return freqMap;
}
