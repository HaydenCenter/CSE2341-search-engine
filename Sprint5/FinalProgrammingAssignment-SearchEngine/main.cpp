#include <iostream>
#include "documenthandler.h"

using namespace std;

int main(int argc, char* argv)
{
    DocumentHandler dh;
    dh.CreateFilesVector(argv[1]);
    return 0;
}
