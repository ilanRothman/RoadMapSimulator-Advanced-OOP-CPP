#include <iostream>
#include "Menu.h"

int main(int argc,char** argv) {
    Menu menu(argc,argv);
    menu.startMenu();
    return 0;
}

//TODO
// - check whether we receive in the load file more than one file.