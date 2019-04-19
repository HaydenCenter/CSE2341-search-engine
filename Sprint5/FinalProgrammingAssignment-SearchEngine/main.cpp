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

    IndexInterface<Word>* theIndex = new AvlTree<Word>;
    DocumentHandler dh;
    dh.CreateFilesVector(argv[1]);
    dh.Parse(theIndex);
    dh.PrintDemoInfo(theIndex,argv[2]);

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << duration.count()/1000000.0 << endl;

    delete theIndex;
}
