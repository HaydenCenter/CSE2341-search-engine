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
#include "query.h"

using namespace std::chrono;

int main(int argc, char* argv[])
{

    cout << argc << endl;
    for(int i = 0; i < argc; i++)
        cout << argv[i] << endl;
    cout << endl;

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


    IndexInterface* theIndex;
    DocumentHandler dh;

    cout << "Welcome to the Search Engine" << endl << endl;
    char userChoice;

    while(true) {
        cout << "Would you like to use an AvlTree (Press 'a') or a Hashtable (Press 'h')?" << endl;
        cin >> userChoice;
        if(userChoice == 'a') {
            theIndex = new AvlTree<Word>;
            break;
        }
        else if(userChoice == 'h') {
            theIndex = new HashtableAdapt;
            break;
        }
        else {
            cout << "Please enter one of the accepted values" << endl;
        }
    }

    while(true) {
        cout << "Would you like to load the index from scratch (Press 's') -OR- from a persisted index (Press 'p')" << endl;
        cin >> userChoice;
        cout << "Loading index..." << endl;
        if(userChoice == 's') {
            dh.getFiles(argv[1]);
            auto start = high_resolution_clock::now();
            dh.parse(theIndex,argv[1]);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            cout << "Runtime: " << duration.count()/1000000.0 << " seconds" << endl;
            break;
        }
        else if(userChoice == 'p') {
            dh.loadIndex(theIndex);
            break;
        }
    }

    cout << "Index was created successfully" << endl << endl;

    while(true) {
        cout << endl << "Menu Options:" << endl;
        cout << "+Maintenance mode (Press 'm')" << endl << "+Interactive mode (Press 'i')" << endl << "+Quit (Press 'q')" << endl;
        cin >> userChoice;
        if(userChoice == 'm') {
            while(true) {
                cout << endl << "Maintenence Mode Menu:" << endl << "+Add Opinions to Index (Press 'a')" << endl;
                cout << "+Clear the Index (Press 'c')" << endl << "+Return to Main Menu (Press 'r')" << endl;
                cin >> userChoice;
                if(userChoice == 'a') {
                    char* newFilePath = new char[255];
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
                cout << endl
                     << "Interactive Mode Menu:" << endl
                     << "+Search the Search Engine (Press 's')" << endl
                     << "+Print Search Engine Statistics (Press 'p')" << endl
                     << "+Return to Main Menu (Press 'r')" << endl;
                cin >> userChoice;
                if (userChoice == 's') {
                    //add search code
                    Query q(theIndex);
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
            cout << "Thanks for using the Search Engine!" << endl;
            cout << "Would you like to save the index to disk?" << endl;
            cout << "(Press 'y' for YES --- Press 'n' for NO)" << endl;
            cin >> userChoice;
            if(userChoice == 'y') {
                dh.saveIndex(theIndex);
            }
            else {
                cout << "The Index was not saved" << endl;
            }

            cout << endl << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Please enter one of the accepted values" << endl;
        }
    }
}
