#ifndef UTILITY_H
#define UTILITY_H

#include<iostream>
#include<vector>
#include<filesystem>
#include<fstream>
#include "menu.h"

using namespace std;
namespace fs = filesystem;

//storing the files available in that folders
inline vector<string> getTestsFiles(const string &folderPath){
    vector<string> files;

    for(const auto &entry : fs::directory_iterator(folderPath)){
        if(entry.path().extension() == ".txt"){
            files.push_back(entry.path().string());
        }
    }

    return files;
}

//showing tests files in that folder
inline void showTests(const vector<string> &files){
    cout << "\nAvailable Test Files: \n\n";

    for(int i=0; i<files.size(); i++){
        cout<<i+1<<". "<<fs::path(files[i]).filename().string()<<endl;
    }
}

// this for running the testfiles
inline string chooseFiles(const string &folderPath){
    vector<string> files = getTestsFiles(folderPath);
    showTests(files);

    int choice;
    cout << "\nEnter your choice: ";
    cin >> choice;

    while(choice < 1 || choice > (int)files.size()){
        cout<<"\n Invalid choice Try Again: ";
        cin >> choice;
    }

    return files[choice - 1];
}

inline string createOutputFiles(const string &inputFile, const string &algorithm){
    fs::create_directories("assignment_01/outputs");
    string filename = fs::path(inputFile).stem().string();

    return "assignment_01/outputs/" + filename + "_" + algorithm + ".txt";
}

// Same as createOutputFiles, but for Assignment 2 (writes to
// assignment_02/outputs instead of assignment_01/outputs).
inline string createOutputFiles2(const string &inputFile, const string &algorithm){
    fs::create_directories("assignment_02/outputs");
    string filename = fs::path(inputFile).stem().string();

    return "assignment_02/outputs/" + filename + "_" + algorithm + ".txt";
}

inline string createOutputFiles3(const string &inputFile, const string &algorithm){
    fs::create_directories("assignment_03/outputs");
    string filename = fs::path(inputFile).stem().string();

    return "assignment_03/outputs/" + filename + "_" + algorithm + ".txt";
}


#endif //UTILITY_H
