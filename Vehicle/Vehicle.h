
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
    map <Junction* , vector < pair < Junction* ,int> > > graph;

    public:
        Vehicle(int st) : stopTime(st) {};

        //getters and setters.

        int getStopTime() const { return stopTime;}

        void setStopTime(int st){stopTime=st;}
};

#endif //EX2_VEHICLE_H
