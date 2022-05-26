#ifndef EX2_ROADMAP_H
#define EX2_ROADMAP_H
#include "Junction.h"
#include "Vehicle.h"
#include "map"


typedef shared_ptr<Junction>  juncPtr;
typedef shared_ptr<pair< pair<string, int>,char> > juncPtrType;

using namespace std;

/**
 * Road map object for holding the graph with all the types of vehicles.
 * Holds a nested class called Edge for the edges of the graph.
 * we didn't implement the bog 5 here for both classes.
 * relying on the defaults since we didn't see a need to change any.
 * **/

class RoadMap {

private:
    class Edge {
    private:
        const string &source;
        const string &dest;
        int duration;
        char type;
    public:
        Edge(const string &source, const string &target, int duration, char type);

        //getters and setters.
        const string &getDest() const;

        int getDuration() const;

        void setDuration(int dur);

        const char &getType() const;
    };

    map<pair<juncPtr ,char > , vector<shared_ptr<Edge> > > graph;

public:

  typedef vector<shared_ptr<RoadMap::Edge> > vecEdge;

    /**
     * adds an Edge that connects two vertices.
     * */
    void addEdge(juncPtr  const &source, juncPtr  const &target, int duration, const char &type,  map<char,int> &stopTimes);

    /**
     * Dijkstra Algorithm
     * by given source and target vertex, the function will print the shortest time it takes to get
     * from one to another.
     * */
    void dijkstra(const string &source, const string &target ,map<char,int> &stopTimes);


    /**
     * return true if junction is in system, else false.
     **/
    bool juncExists(juncPtr const&);


    /**
     * creates the vertices of each vehicle type for given junction.
     * */
    void makeVertices(juncPtr const& junc);

    /**
     * connects the edges between source and target.
     * */
    void connectEdges(const juncPtr& source, const string& target, char& type ,map<char,int> &stopsTimes);

    /*
     * updates the weights of the edges.
      */
    void updateEdges(const juncPtr& source, const juncPtr  &target, int duration, const char &type,  map<char,int> &stopsTimes);


    /*
     *   return true if the edge is in system, else false.
      */
    bool checkEdgeExist(const juncPtr& source, const juncPtr  &, char type);


    /*
     * if the edge does not exist it creates one.
     * */
    void createEdges(const juncPtr& source, const juncPtr  &target,map<char,int> &stopsTimes);

    /*
     * getters.
     * */

    juncPtr getSource(const string &source) const;

    vecEdge& getAdj(juncPtrType& ptr);

    vecEdge& getTargetVector(juncPtr const& source, char type);

};


#endif //EX2_ROADMAP_H
