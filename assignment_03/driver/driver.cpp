#include "driver.h"

void assignment03Driver(){
     while(true){
        int choice = Menu::showAlgorithmMenu2();
        switch(choice){
            case 1:
                //gradient decent
                break;
            case 2:
                maxflow_mincut_driver();
                break;
            case 0:
                cout<<"Go Back"<<endl;
                return;
            default:
                break;
        }
    }
}