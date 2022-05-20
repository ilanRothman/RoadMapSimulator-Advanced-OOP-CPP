#ifndef EX2_ROADMAP_H
#define EX2_ROADMAP_H
#include "Junction/Junction.h"
#include "Vehicle/Vehicle.h"
#include "map"


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

    map<pair<shared_ptr<Junction>,char > , vector<shared_ptr<Edge> > > graph;

public:
    RoadMap();

    void addEdge(shared_ptr<Junction> const &source, shared_ptr<Junction> const &target, int duration, const char &type);

//    void printMap() const;

    shared_ptr<Junction> getSource(const string &source) const;

    void dijkstra(const string &source, const string &target);

    bool juncExists(shared_ptr<Junction> const&, const char&);

    void makeVertices(shared_ptr<Junction> const& junc);

    void connectEdges(const shared_ptr<Junction>& source, const string& target, char& type);

    void updateEdges(const shared_ptr<Junction> &source, const shared_ptr<Junction> &target, int duration, const char &type);

    bool checkEdgeExist(const shared_ptr<Junction> &source, const shared_ptr<Junction> &target);

    void createEdges(const shared_ptr<Junction> &source, const shared_ptr<Junction> &target);

    vector<shared_ptr<Edge> >& getAdj(shared_ptr<pair< pair<string, int>,char> >& ptr);
};
#endif //EX2_ROADMAP_H
