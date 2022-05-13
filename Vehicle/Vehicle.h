
#ifndef EX2_VEHICLE_H
#define EX2_VEHICLE_H

#include <vector>
#include "../Junction/Junction.h"
#include "map"
#include "memory"

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

        void printMap();

};

#endif //EX2_VEHICLE_H
