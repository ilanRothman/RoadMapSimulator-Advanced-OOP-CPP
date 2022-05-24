#ifndef EX2_ROADMAP_H
#define EX2_ROADMAP_H
#include "Junction/Junction.h"
#include "Vehicle/Vehicle.h"
#include "map"

typedef shared_ptr<Junction>  juncPtr;
typedef shared_ptr<pair< pair<string, int>,char> > juncPtrType;

using namespace std;

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

        const string &getSource() const;

        const string &getDest() const;

        int getDuration() const;

        void setDuration(int dur);

        const char &getType() const;
    };

    map<pair<juncPtr ,char > , vector<shared_ptr<Edge> > > graph;

public:
    RoadMap();

    void addEdge(juncPtr  const &source, juncPtr  const &target, int duration, const char &type,  map<char,int> &stopTimes);

    void printMap() const;

    juncPtr  getSource(const string &source) const;

    void dijkstra(const string &source, const string &target ,map<char,int> &stopTimes);

    bool juncExists(juncPtr const&);

    void makeVertices(juncPtr const& junc);

    void connectEdges(const juncPtr& source, const string& target, char& type ,map<char,int> &stopsTimes);

    void updateEdges(const juncPtr& source, const juncPtr  &target, int duration, const char &type,  map<char,int> &stopsTimes);

    bool checkEdgeExist(const juncPtr& source, const juncPtr  &target);

    void createEdges(const juncPtr& source, const juncPtr  &target,map<char,int> &stopsTimes);

    vector<shared_ptr<Edge> >& getAdj(juncPtrType& ptr);
};
#endif //EX2_ROADMAP_H
