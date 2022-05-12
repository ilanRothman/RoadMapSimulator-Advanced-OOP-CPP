
#ifndef EX2_MENU_H
#define EX2_MENU_H

#include "FileMgr.h"
#include "RoadMap.h"
#include "Vehicle/Bus.h"
#include "Vehicle/Rail.h"
#include "Vehicle/Sprinter.h"
#include "Vehicle/Tram.h"
#include "Junction/Junction.h"
#include "iostream"
#include "Junction/interCity.h"
#include "Junction/Central.h"
#include "Junction/Stad.h"
#include "map"

using namespace std;

class Menu{
    private:
        FileMgr files;
        Bus bus;
        Rail rail;
        Sprinter sprinter;
        Tram tram;
        RoadMap generalMap;
        InterCity interCity;
        Central central;
        Stad stad;
        map<string,int> commands;

    public:
        Menu(int argc, char** argv);
        void config();
        void startMenu();
        void mapInit();

};

#endif //EX2_MENU_H
