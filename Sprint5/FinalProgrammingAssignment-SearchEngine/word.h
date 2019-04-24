#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Word
{
public:
    Word();
    Word(string);
    Word(string,map<string,int>);
    bool operator==(const Word) const;
    bool operator<(const Word) const;
    bool operator>(const Word) const;
    string& getWordText();
    map<string, int> &getMap();
    void setWordText(string);
    void setMap(map<string,int>);
    vector<pair<double,string>> relevantDocuments(int);
private:
    string wordText;
    map<string,int> freqMap;
};

#endif // WORD_H
