#include "../assignment_01/driver/driver.h"
#include <iostream>
#include "menu.h"

int main() {

    while(true){
        int choice = Menu::showAssignmetMenu();

        switch(choice){
            case 1:
                assignment01driver();
                break;
            case 0:
                cout<<"Exited"<<endl;
                return 0;
            default:
                cout<<"Invalid Input"<<endl;
        }
    }

    return 0;
}