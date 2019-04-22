#include "word.h"

Word::Word()
{
    wordText = "";
}

Word::Word(string s) {
    wordText = s;
}

Word::Word(string s, map<int,int> m) {
    wordText = s;
    frequencyMap = m;
}

bool Word::operator==(const Word rhs) const {
    return wordText == rhs.wordText;
}

bool Word::operator<(const Word rhs) const {
    return wordText < rhs.wordText;
}

bool Word::operator>(const Word rhs) const {
    return wordText > rhs.wordText;
}

string &Word::getWordText() {
    return wordText;
}

void Word::setWordText(string s) {
    wordText = s;
}

void Word::setMap(map<int,int> mapToSet) {
    frequencyMap = mapToSet;
}

map<int, int>& Word::getMap() {
    return frequencyMap;
}
