
#ifndef EX2_VEHICLE_H
#define EX2_VEHICLE_H

#include <vector>
#include "../Junction/Junction.h"
    using namespace std;


class Vehicle {
    private:
        int stopTime;
        vector< pair <Junction*, vector< pair< Junction*, int> > > > graph;
    public:
        Vehicle(int st) : stopTime(st) {};
        virtual ~Vehicle() = 0; // abstract

        //getters and setters.

        int getStopTime() const { return stopTime;}

        void setStopTime(int st){stopTime=st;}
};

#endif //EX2_VEHICLE_H
