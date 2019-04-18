#include <iostream>
#include <fstream>
#include "documenthandler.h"
#include <json.hpp>
#include <sstream>
#include "porter2_stemmer.h"
#include <chrono>
#include "avltree.h"
#include "indexinterface.h"

using namespace std::chrono;

int main(int argc, char* argv[])
{
    auto start = high_resolution_clock::now();

    cout << argc << endl;
    for(int i = 0; i < argc; i++)
        cout << argv[i];

    IndexInterface<Word>* theIndex = new AvlTree<Word>;
    DocumentHandler dh;
    dh.CreateFilesVector(argv[1]);
    dh.Parse(theIndex);

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    cout << duration.count()/1000000.0 << endl;
}
