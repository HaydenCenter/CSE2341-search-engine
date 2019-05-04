#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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

void createIndex(IndexInterface*& theIndex, DocumentHandler& dh, char* filesToLoad) {
    char userChoice;
    while(true) {
        cout << endl;
        cout << "What type of index would you like to use?" << endl;
        cout << "(1) - AvlTree" << endl;
        cout << "(2) - HashTable" << endl;
        cout << "Select one: ";
        cin >> userChoice;
        if(userChoice == '1') {
            theIndex = new AvlTree<Word>;
            break;
        }
        else if(userChoice == '2') {
            theIndex = new HashtableAdapt;
            break;
        }
        else {
            cout << "Please enter one of the accepted values" << endl;
        }
    }

    while(true) {
        cout << endl << "How would you like it build the index?" << endl;
        cout << "(1) - Create new index" << endl;
        cout << "(2) - Load saved index" << endl;
        cout << "Select one: ";
        cin >> userChoice;
        if(userChoice == '1') {
            cout << endl << "Loading index..." << endl;
            dh.getFiles(filesToLoad);
            auto start = high_resolution_clock::now();
            dh.parse(theIndex,filesToLoad);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            cout << "Index Loaded" << endl;
            cout << "Runtime: " << duration.count()/1000000.0 << " seconds" << endl;
            break;
        }
        else if(userChoice == '2') {
            cout << endl << "Loading index..." << endl;
            auto start = high_resolution_clock::now();
            dh.loadIndex(theIndex);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start);
            cout << "Index Loaded" << endl;
            cout << "Runtime: " << duration.count()/1000000.0 << " seconds" << endl;
            break;
        }
        else {
            cout << "Please enter one of the accepted values" << endl;
        }
    }
}

int main(int argc, char* argv[])
{
    cout << argc << endl;
    for(int i = 0; i < argc; i++)
        cout << argv[i] << endl;
    cout << endl;

    IndexInterface* theIndex;
    DocumentHandler dh;

    cout << "Welcome to the Search Engine" << endl;
    char userChoice;
    createIndex(theIndex,dh,argv[1]);

    while(true) {
        cout << endl << "Main Menu:" << endl;
        cout << "(1) - Interactive Mode" << endl;
        cout << "(2) - Maintenance Mode" << endl;
        cout << "(3) - Quit" << endl;
        cout << "Select one: ";
        cin >> userChoice;
        if(userChoice == '1') {
            while(true) {
                cout << endl << "Interactive Mode:" << endl;
                cout << "(1) - Search" << endl;
                cout << "(2) - Print Statistics" << endl;
                cout << "(3) - Return to Main Menu" << endl;
                cout << "Select One: ";
                cin >> userChoice;
                if (userChoice == '1') {
                    cout << endl;
                    Query q(theIndex);
                    if(q.getRelevantFiles().size() != 0)
                    {
                        SearchResultHandler SRH(q.getRelevantFiles());
                        SRH.displaySearchResults();
                        bool RAN = false;
                        while(true)
                        {
                            cout << endl << "Would you like to open a result? (y/n) ";
                            cin >> userChoice;
                            if(userChoice == 'y')
                            {
                                if(RAN)
                                    SRH.displaySearchResults();
                                while(true)
                                {
                                    cout << endl << "Which result would you like to open?" << endl;
                                    cout << "Select one: ";
                                    string choice;
                                    cin >> choice;
                                    int docChoice = -1;
                                    if(choice.length() == 1)
                                        docChoice = choice[0] - '0';
                                    else if(choice[0] == '1')
                                        docChoice = (choice[1] - '0') + 10;
                                    if(SRH.openFileInfo(docChoice - 1))
                                        break;
                                    else
                                        cout << "Please enter one of the accepted values" << endl;
                                }
                                RAN = true;
                            }
                            else if(userChoice == 'n')
                            {
                                break;
                            }
                            else
                            {
                                cout << "Please enter one of the accepted values" << endl;
                            }
                        }
                    }
                    else
                        cout << "No results found" << endl;
                }
                else if(userChoice == '2') {
                    cout << endl;
                    dh.printStatistics(theIndex);
                }
                else if(userChoice == '3') {
                    break;
                }
                else {
                    cout << "Please enter one of the accepted values" << endl;
                }
            }
        }
        else if(userChoice == '2') {
            cout << endl;
            while(true) {
                cout << "Maintenence Mode:" << endl;
                cout << "(1) - Add Opinions" << endl;
                cout << "(2) - Clear the Index" << endl;
                cout << "(3) - Return to Main Menu" << endl;
                cout << "Select one: ";
                cin >> userChoice;
                if(userChoice == '1') {
                    cout << endl;
                    char* newFilePath = new char[255];
                    cout << "Please enter a new file path to add files: ";
                    cin >> newFilePath;
                    try
                    {
                        dh.getFiles(newFilePath);
                        dh.parse(theIndex,newFilePath);
                    }
                    catch(invalid_argument e)
                    {
                        cout << e.what() << endl;
                    }
                    delete[] newFilePath;
                }
                else if(userChoice == '2') {
                    cout << endl;
                    cout << "Clearing the Index..." << endl;
                    theIndex->makeEmpty();
                    dh.clearStatistics();
                    cout << "Index Cleared" << endl;
                    while(true)
                    {
                        cout << endl << "Would you like to build a new index? (y/n) ";
                        cin >> userChoice;
                        if(userChoice == 'y')
                        {
                            delete theIndex;
                            createIndex(theIndex,dh,argv[1]);
                        }
                        else if(userChoice == 'n')
                            break;
                        else
                            cout << "Please enter one of the accepted values" << endl;
                    }
                }
                else if(userChoice == '3') {
                    break;
                }
                else{
                    cout << "Please enter one of the accepted values" << endl;
                }
                cout << endl;
            }
        }
        else if(userChoice == '3') {
            cout << endl;
            cout << "Thanks for using the Search Engine!" << endl << endl;
            cout << "Would you like to save the index to disk? (y/n) ";
            cin >> userChoice;
            cout << endl;
            if(userChoice == 'y') {
                auto start = high_resolution_clock::now();
                dh.saveIndex(theIndex);
                auto end = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(end - start);
                cout << "Runtime: " << duration.count()/1000000.0 << " seconds" << endl;
            }
            else {
                cout << "The Index was not saved" << endl;
            }

            cout << endl << "Goodbye!" << endl << endl;
            break;
        }
        else {
            cout << "Please enter one of the accepted values" << endl;
        }
    }
}
