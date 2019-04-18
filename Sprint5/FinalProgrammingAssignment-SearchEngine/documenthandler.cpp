#include "documenthandler.h"

DocumentHandler::DocumentHandler()
{

}

void DocumentHandler::CreateFilesVector(char* c) {
    string extn = ".json";
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(c)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            int len = strlen(ent->d_name);
            if (ent->d_type == DT_REG &&
                len > extn.length() &&
                strcmp(ent->d_name + len - extn.length(), extn.c_str()) == 0)
                files.push_back(ent->d_name);
        }
        closedir(dir);
    }
    else {
        throw invalid_argument("Provided path could not be opened");
    }
}

void DocumentHandler::parse()
{
    //Used to parse a small random sample
    srand(time(NULL));
    int x = rand() % 68390;

    // To parse full dataset:
    // (int i = 0; i < files.size(); i++)
    for(int i = x; i < x + 100; i++)
    {
        json j;
        ifstream inFile;
        inFile.open("../scotus/" + files[i]);
        if(!inFile.is_open())
        {
            throw exception();
        }

        //Stores entire file into json object
        inFile >> j;

        //Stores document ID to emplace into map
        int id = j["id"];
        cout << id << endl;
        string str = j["plain_text"];
        if(str == "")
            str = j["html"];
        istringstream iss(str);
        while(!iss.eof())
        {
            string word;
            iss >> word;
            cout << word << " -> ";
            Porter2Stemmer::trim(word);
            cout << word << " -> ";
            Porter2Stemmer::stem(word);
            cout << word << endl;
        }

        cout << endl << files[i] << endl << endl;
    }
}
