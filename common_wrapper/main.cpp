#include <iostream>
#include "../assignment_01/driver/driver.h"
#include "../assignment_02/driver/driver.h"
#include "menu.h"

int main() {

    while(true){
        int choice = Menu::showAssignmentMenu();

        switch(choice){
            case 1:
                assignment01Driver();
                break;
            case 2:
                assignment02Driver();
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
