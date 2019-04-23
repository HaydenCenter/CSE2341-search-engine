#ifndef WORD_H
#define WORD_H
#include <iostream>
#include <map>
using namespace std;

class Word
{
public:
    Word();
    Word(string);
    Word(string,map<int,int>);
    bool operator==(const Word) const;
    bool operator<(const Word) const;
    bool operator>(const Word) const;
    string& getWordText();
    map<int,int>& getMap();
    void setWordText(string);
    void setMap(map<int,int>);
private:
    string wordText;
    map<int,int> freqMap;
};

#endif // WORD_H
