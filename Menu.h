
#ifndef EX2_MENU_H
#define EX2_MENU_H

#include "FileMgr.h"
#include "RoadMap.h"
#include "Vehicle/Bus.h"
#include "Vehicle/Rail.h"
#include "Vehicle/Sprinter.h"
#include "Vehicle/Tram.h"
#include "iostream"
#include "map"
#include <fstream>
#include <sstream>
#include "memory"

using namespace std;

class Menu{
    private:
        FileMgr files;
        Bus bus;
        Rail rail;
        Sprinter sprinter;
        Tram tram;
        RoadMap generalMap;
        map<string,int> commands;
        map<string,int> stationTimes;

    public:
        Menu(int argc, char** argv);
        void config(); //setting default values according to config file.
        void startMenu();//main menu of program.
        void mapInit(); //menu keys for the menu switch case and junction transit times.
        void addEdge(string& option,string& source,string& target,string& duration); //adding an edge to the vehicle map and the general map.
        shared_ptr<Junction> createJunc(string& name); //separating the menu option and the command.
        void print() const;
        void outBound(const string& source) const;

};

#endif //EX2_MENU_H
