#include <iostream>
#include <fstream>
#include "documenthandler.h"
#include <json.hpp>
#include <sstream>
#include "porter2_stemmer.h"
#include <chrono>
#include "indexinterface.h"
#include "avltree.h"
#include "hashtableadapt.h"

using namespace std::chrono;

int main(int argc, char* argv[])
{
//    auto start = high_resolution_clock::now();

//    cout << argc << endl;
//    for(int i = 0; i < argc; i++)
//        cout << argv[i] << endl;
//    cout << endl;

//    IndexInterface* theIndex = new AvlTree<Word>;
//    DocumentHandler dh;
//    dh.getFiles(argv[1]);

//    dh.parse(theIndex,argv);
//    dh.PrintDemoInfo(theIndex,argv[2]);

//    string word(argv[2]);
//    Porter2Stemmer::trim(word);
//    Porter2Stemmer::stem(word);
//    Word w(word);
//    vector<pair<double,string>> v1 = theIndex->search(w)->relevantDocuments(theIndex->getNumDocsParsed());
//    for(unsigned int i = 0; i < v1.size(); i++)
//    {
//        cout << v1[i].second << " relevancy = " << v1[i].first << endl;
//    }

//    dh.saveIndex(theIndex);
//    delete theIndex;

//    auto end = high_resolution_clock::now();
//    auto duration = duration_cast<microseconds>(end - start);
//    cout << "Runtime: " << duration.count()/1000000.0 << " seconds" << endl;


    IndexInterface* theIndex;
    DocumentHandler dh;

    cout << "Welcome to the Search Engine" << endl << endl;
    char userChoice;
    while(true) {
        cout << "Menu Options:" << endl;
        cout << "+Maintenance mode (Press 'm')" << endl << "+Interactive mode (Press 'i')" << endl << "+Quit (Press 'q')" << endl;
        cin >> userChoice;
        if(userChoice == 'm') {
            while(true) {
                cout << endl << "Maintenence Mode Menu:" << endl << "+Add Opinions to Index (Press 'a')" << endl;
                cout << "+Clear the Index (Press 'c')" << endl << "+Return to Main Menu (Press 'r')" << endl;
                cin >> userChoice;
                if(userChoice == 'a') {
                    char* newFilePath;
                    cout << "Please enter a new file path to add files: ";
                    cin >> newFilePath;
                    dh.getFiles(newFilePath);
                    dh.parse(theIndex,newFilePath);
                }
                else if(userChoice == 'c') {
                    cout << "Clearing the Index... ";
                    theIndex->makeEmpty();
                    cout << "Complete" << endl;
                }
                else if(userChoice == 'r') {
                    break;
                }
                else{
                    cout << "Please enter one of the accepted values" << endl;
                }
            }

        }
        else if(userChoice == 'i') {
            while(true) {
                cout << endl << "Interactive Mode Menu:" << endl << "+Build the Index (Press 'b')" << endl;
                cout << "+Search the Search Engine (Press 's')" << endl << "+Print Search Engine Statistics (Press 'p')" << endl;
                cout << "+Return to Main Menu (Press 'r')" << endl;
                cin >> userChoice;
                if(userChoice == 'b') {
                    cout << "Would you like to use an AvlTree or a Hashtable to store the Index? ('a' for AvlTree -OR- 'h' for Hashtable): ";
                    cin >> userChoice;
                    if(userChoice == 'a') {
                        theIndex = new AvlTree<Word>;
                    }
                    else if(userChoice == 'h') {
                        theIndex == new HashtableAdapt;
                    }
                    cout << "Would you like to load the index from scratch (Press 's') -OR- from a persisted index (Press 'p')" << endl;
                    cin >> userChoice;
                    cout << "Loading index..." << endl;
                    if(userChoice == 's') {
                        dh.getFiles(argv[1]);
                        dh.parse(theIndex,argv[1]);
                    }
                    else if(userChoice == 'p') {
                        dh.loadIndex(theIndex);
                    }
                    cout << "Index was created successfully" << endl;
                }
                else if (userChoice == 's') {
                    //add search code
                }
                else if(userChoice == 'p') {
                    dh.printStatistics(theIndex);
                }
                else if(userChoice == 'r') {
                    break;
                }
                else {
                    cout << "Please enter one of the accepted values" << endl;
                }
            }

        }
        else if(userChoice == 'q') {
            cout << "Thanks for using the Search Engine!" << endl << endl << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Please enter one of the accepted values" << endl;
        }
    }
}
