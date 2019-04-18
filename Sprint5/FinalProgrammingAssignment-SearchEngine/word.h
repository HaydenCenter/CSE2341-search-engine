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
    bool operator==(Word);
    string getWordText();
    void setWordText(string);
    void setMapPair(int,int);
private:
    string wordText;
    map<int,int> frequencyMap;
};

#endif // WORD_H
