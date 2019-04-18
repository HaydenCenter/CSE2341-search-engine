#include "word.h"

Word::Word()
{

}

Word::Word(string s) {
    wordText = s;
}

bool Word::operator==(Word wordToCompare) {
    return wordText == wordToCompare.wordText;
}

string Word::getWordText() {
    return wordText;
}

void Word::setWordText(string s) {
    wordText = s;
}

void Word::setMapPair(int x, int y) {
    frequencyMap.emplace(x,y);
}
