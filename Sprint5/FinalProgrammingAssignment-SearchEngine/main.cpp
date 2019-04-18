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

    IndexInterface<Word>* theIndex = new AvlTree<Word>;
    DocumentHandler dh;
    dh.CreateFilesVector(argv[1]);
    dh.Parse(theIndex);
    dh.PrintDemoInfo(theIndex,argv[2]);

}
