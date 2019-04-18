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
    bool operator==(Word);
    string getWordText();
    void setWordText(string);
    void setMap(map<int,int>);
    map<int,int> getMap();
private:
    string wordText;
    map<int,int> frequencyMap;
};

#endif // WORD_H
