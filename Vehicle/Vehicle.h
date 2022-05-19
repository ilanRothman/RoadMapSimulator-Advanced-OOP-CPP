
#ifndef EX2_VEHICLE_H
#define EX2_VEHICLE_H

#include <vector>
#include "../Junction/Junction.h"
#include "map"
#include "memory"
#include "iostream"
#include "list"
typedef map<shared_ptr<Junction>, vector<pair<shared_ptr<Junction>, int> > > graphMap;

using namespace std;

class Vehicle {
    private:
    int stopTime;
    graphMap graph;
    graphMap turnedGraph;

    public:
        Vehicle(int st) : stopTime(st) {};

        void dijkstra(const string &source, const string &target);
        //getters and setters.
        const graphMap &getGraph() const;

        int getStopTime() const { return stopTime;}

        void setStopTime(int st){stopTime=st;}

        void addEdge(shared_ptr<Junction>const& source, shared_ptr<Junction>const& target, int duration);

        void printMap() const;

        void BFS(string const&  juncName, const graphMap& gr) const;

        shared_ptr<Junction> getSource(string const& source) const;

        void updateTurnedGraph();

        const graphMap &getTurnedGraph() const;

        const vector<pair<shared_ptr<Junction>, int> > & getAdj(string& source);


//        void dfsHelper(const string& target);
//
//        void DFS(const string& source,const string& target, map<string,bool> & visited, bool& toPrint);


};

#endif //EX2_VEHICLE_H
