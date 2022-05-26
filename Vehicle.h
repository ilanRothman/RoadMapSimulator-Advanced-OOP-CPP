
#ifndef EX2_VEHICLE_H
#define EX2_VEHICLE_H

#include <vector>
#include "Junction.h"
#include "map"
#include "memory"
#include "iostream"
#include "list"
typedef map<shared_ptr<Junction>, vector<pair<shared_ptr<Junction>, int> > > graphMap;
typedef shared_ptr<Junction> juncPtr;
typedef vector<pair<juncPtr,int> > vecJI;
typedef shared_ptr<pair<string,int> > juncDist;

using namespace std;


/**
 * Class Vehicle is an abstract class.
 * the derived classes will each hold a graph of its own with the given edges that will be uploaded
 * during the beginning of the program or during run time.
 * there will be no need for the Greatest Five since the defaults will work fine.
 */

class Vehicle {
    private:
    int stopTime;
    graphMap graph;
    graphMap turnedGraph;

    public:
    /**
     * Constructor
     * */

        explicit Vehicle(int st) : stopTime(st) {};
    /**
     * Dijkstra Algorithm
     * by given source and target vertex, the function will print the shortest time it takes to get
     * from one to another.
     * */
        void dijkstra(const string &source, const string &target);


        /**
         * By given the parameters listed below it will add an edge between the Source and Target
         * with the given duration.
         * */
        void addEdge(shared_ptr<Junction>const& source, shared_ptr<Junction>const& target, int duration);


        /**
         * prints the map
         * */
        void printMap() const;

        /**
         * BFS Algorithm
         * by given Source and certain map, the function will print
         * all the vertices the source can reach.
         * */

        void BFS(string const&  juncName, const graphMap& gr) const;

        /**
         * transfers all the edges in the graph to the opposite dircetion
         * */
        void updateTurnedGraph();

        /**
         * update the target in the graph.
         * */

        void updateTargetInGraph(juncPtr const& target);

    /**
    * getters and setters
    *
    * */
        const graphMap &getGraph() const;

        void setStopTime(int st){stopTime=st;}

        shared_ptr<Junction> getSource(string const& source) const;

        const graphMap &getTurnedGraph() const;

        const vector<pair<shared_ptr<Junction>, int> > & getAdj(string& source);

};

#endif //EX2_VEHICLE_H
