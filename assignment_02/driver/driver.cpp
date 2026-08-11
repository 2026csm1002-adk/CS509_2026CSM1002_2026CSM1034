#include "../../common_wrapper/menu.h"
#include "driver.h"

void assignment02Driver(){

    while(true){
        int choice = Menu::showAlgorithmMenu2();
        switch(choice){
        case 1:
            tcDriver();
            break;
        case 2:
            bcDriver();
            break;
        case 3:
            ccDriver();
            break;
        case 0:
            cout<<"Go Back"<<endl;
            return;
        default:
            break;
    }
    }

}