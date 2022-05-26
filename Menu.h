
#ifndef EX2_MENU_H
#define EX2_MENU_H

#include "FileMgr.h"
#include "RoadMap.h"
#include "Bus.h"
#include "Rail.h"
#include "Sprinter.h"
#include "Tram.h"
#include "iostream"
#include "map"
#include <fstream>
#include <sstream>
#include "memory"

using namespace std;

/**
 *  Menu object for running the program. enter the command for what you want to do.
 *  we didn't implement the big 5 here because we could rely on the defaults for our needs.
 * */

class Menu{
    private:
        FileMgr files; // holds the file paths.
        Bus bus;
        Rail rail;
        Sprinter sprinter;
        Tram tram;
        RoadMap generalMap;
        map<string,int> commands; // map for the menu commands.
        map<string,int> stationTimes; // map for the transit times.
        map<char,int> stopTimes; // map for the stop times.

    public:
        Menu(int argc, char** argv);

        /*
         * setting default values according to config file.
        */
        void config();


        /*
         * main menu of program.
         */
        void startMenu();


        /*
         * menu keys for the menu switch case and junction transit times.
         */
        void mapInit();


        /*
         * adding an edge to the vehicle map and the general map.
         */
        void addEdge(string& option,string& source,string& target,string& duration);


        /*
         * checking what type of junction and creating it accordingly.
         */
        shared_ptr<Junction> createJunc(string& name);

        /*
         * printing the maps of the vehicle objects.
         */
        void print() const;

        /*
         * the destinations reachable from given source using the BFS algorithm.
         */
        void outBound(const string& source) const;

        /*
         * the junctions you can reach the source from using the BFS algorithm.
        */
        void inBound(const string& source);

        /*
         * given the command with a source and dest it returns
         * all the times it will take using each vehicle type.
         */
        void uniExpress(const string &command);

        /*
         * given the command with a source and dest it returns
         * the quickest time reachable to the destination including all vehicle types.
         * */
        void multiExpress(string command);
};

#endif //EX2_MENU_H
