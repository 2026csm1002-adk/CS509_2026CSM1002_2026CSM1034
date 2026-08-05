#include "../../common_wrapper/menu.h"
#include "driver.h"

void assignment01Driver(){

    while(true){
        int choice = Menu::showAlgorithmMenu();
        switch(choice){
        case 1:
            bfsDriver(); //call bfsDriver
            break;
        case 2:
            dfsDriver(); //call dfsDriver
            break;
        case 3:
            ssspDriver(); //call ssspDriver
            break;
        case 0:
            cout<<"Go Back"<<endl;
            return;
        default:
            // Handle invalid choice
            break;
    }
    }
    
}