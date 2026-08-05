#include<iostream>
#include "menu.h"

using namespace std;

int Menu::showAssignmentMenu(){
    cout <<"\n==========================================\n";
    cout <<"       Buddy CS509 Assignment Menu            \n";
    cout <<"==========================================\n";

    cout<<" 1. Assignment 1"<<endl;
    cout<<" 0. Exit"<<endl;

    int choose=-1;

    cout<<"Enter your choice: ";
    cin>>choose;
    return choose;
}

int Menu::showAlgorithmMenu(){
    cout<<"\n=============Algorithm Menu============="<<endl;
    cout<<"1. BFS"<<endl;
    cout<<"2. DFS"<<endl;
    cout<<"3. Single Source Shortest Path(SSSP)"<<endl;
    cout<<"0. Back"<<endl;
    int choose=-1;
    cout<<"Enter your choice: ";
    cin>>choose;
    return choose;
}

int Menu::showInputMenu(){
    cout<<"\n=============Input Menu============="<<endl;
    cout<<"1. Run Selected Test "<<endl;
    cout<<"2. Run all Tests Cases"<<endl;
    cout<<"3. Run Custom Test"<<endl;
    cout<<"0. Go Back"<<endl;
    int choose=-1;
    cout<<"Enter your choice: ";
    cin>>choose;
    return choose;
}