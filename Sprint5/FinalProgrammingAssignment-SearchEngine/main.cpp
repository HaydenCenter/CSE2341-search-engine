#include <iostream>
#include <fstream>
#include "documenthandler.h"
#include <json.hpp>
#include <sstream>
#include "porter2_stemmer.h"
#include <chrono>
#include "indexinterface.h"
#include "avltree.h"

using namespace std::chrono;

int main(int argc, char* argv[])
{
    auto start = high_resolution_clock::now();

    cout << argc << endl;
    for(int i = 0; i < argc; i++)
        cout << argv[i] << endl;
    cout << endl;

    IndexInterface<Word>* theIndex = new AvlTree<Word>;
    DocumentHandler dh;
    dh.getFiles(argv[1]);

    dh.parse(theIndex);
    theIndex->print();
    dh.PrintDemoInfo(theIndex,argv[2]);

    string word(argv[2]);
    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    Word w(word);
    vector<pair<double,string>> v1 = theIndex->search(w)->relevantDocuments(theIndex->getNumDocsParsed());
    for(unsigned int i = 0; i < v1.size(); i++)
    {
        cout << v1[i].second << " relevancy = " << v1[i].first << endl;
    }

    dh.saveIndex(theIndex);
    delete theIndex;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Runtime: " << duration.count()/1000000.0 << " seconds" << endl;
}
