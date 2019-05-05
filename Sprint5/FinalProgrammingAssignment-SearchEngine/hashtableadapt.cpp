#include "hashtableadapt.h"

HashtableAdapt::HashtableAdapt()
{
    numDocsParsed = 0;
    averageWordsPerFile = 0;
}

HashtableAdapt::~HashtableAdapt() {}

int& HashtableAdapt::getSize() {
    return theIndex.getSize();
}

int& HashtableAdapt::getNumDocsParsed() {
    return numDocsParsed;
}

double& HashtableAdapt::getAverageWordsPerFile() {
    return averageWordsPerFile;
}


Word* HashtableAdapt::insert(Word& elementToAdd) {
    return theIndex.insert(elementToAdd.getWordText(),elementToAdd);
}

void HashtableAdapt::makeEmpty() {
    theIndex.makeEmpty();
    numDocsParsed = 0;
    averageWordsPerFile = 0;
}

bool HashtableAdapt::isEmpty() const {
    return theIndex.isEmpty();
}

bool HashtableAdapt::contains(Word& search) {
    return theIndex.contains(search.getWordText(),search);
}

Word* HashtableAdapt::search(Word search) {
    return theIndex.search(search.getWordText(),search);
}

void HashtableAdapt::print() {
    theIndex.print();
}

void HashtableAdapt::output(ofstream& outFS) {
    theIndex.output(outFS);
}

vector<pair<int,Word*>> HashtableAdapt::findMostFrequentWords()
{
    return theIndex.findMostFrequentWords();
}
