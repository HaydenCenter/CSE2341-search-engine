#include "hashtableadapt.h"

HashtableAdapt::HashtableAdapt()
{
    numDocsParsed = 0;
}

HashtableAdapt::~HashtableAdapt() {}

int& HashtableAdapt::getSize() {
    return theIndex.getSize();
}

int& HashtableAdapt::getNumDocsParsed() {
    return numDocsParsed;
}

int& HashtableAdapt::getAverageWordsPerFile() {
    return averageWordsPerFile;
}


Word* HashtableAdapt::insert(Word& elementToAdd) {
    return theIndex.insert(elementToAdd.getWordText(),elementToAdd);
}

void HashtableAdapt::makeEmpty() {
    theIndex.makeEmpty();
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
