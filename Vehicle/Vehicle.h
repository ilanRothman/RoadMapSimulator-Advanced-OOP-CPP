
#ifndef EX2_VEHICLE_H
#define EX2_VEHICLE_H

#include <vector>
#include "../Junction/Junction.h"
#include "map"
#include "memory"
#include "iostream"
#include "list"
using namespace std;


class Vehicle {
    private:
    int stopTime;
    map <shared_ptr<Junction> , vector < pair < shared_ptr<Junction> ,int> > > graph;

    public:
        Vehicle(int st) : stopTime(st) {};

        //getters and setters.

        int getStopTime() const { return stopTime;}

        void setStopTime(int st){stopTime=st;}

        void addEdge(shared_ptr<Junction>const& source, shared_ptr<Junction>const& target, int duration);

        void printMap() const;

        void BFS(string const&  juncName) const;

        shared_ptr<Junction> getSource(string const& source) const;

        void dfsHelper(const string& target);

        void DFS(const string& source,const string& target, map<string,bool> & visited, bool& toPrint);

        map <shared_ptr<Junction>, vector < pair < shared_ptr<Junction> ,int> > >& turnedGraph();

};

#endif //EX2_VEHICLE_H
