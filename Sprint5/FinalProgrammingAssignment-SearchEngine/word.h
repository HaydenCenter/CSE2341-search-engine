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
    Word(string,map<string,pair<int,double>>);
    bool operator==(const Word) const;
    bool operator<(const Word) const;
    bool operator>(const Word) const;
    friend ostream& operator<<(ostream&, const Word&);
    string& getWordText();
    map<string,pair<int,double>>& getMap();
    void setWordText(string);
    void setMap(map<string,pair<int,double>>);
    vector<pair<string,double>> relevantDocuments(int);
    int getTotalFrequency();
private:
    string wordText;
    map<string,pair<int,double>> freqMap;
};

#endif // WORD_H
