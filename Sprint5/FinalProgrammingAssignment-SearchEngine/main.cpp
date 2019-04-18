#include <iostream>
#include <fstream>
#include "documenthandler.h"
#include <json.hpp>
#include <sstream>
#include "porter2_stemmer.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << argc << endl;
    for(int i = 0; i < argc; i++)
        cout << argv[i];

    DocumentHandler dh;
    dh.CreateFilesVector(argv[1]);
    dh.parse();
}
