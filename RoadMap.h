#ifndef EX2_ROADMAP_H
#define EX2_ROADMAP_H
#include "Junction/Junction.h"
#include "Vehicle/Vehicle.h"
#include "map"


using namespace std;

class RoadMap{
private:
    map <shared_ptr<Junction> , vector < pair < shared_ptr<Junction> ,int> > > graph;

public:
    void addEdge(shared_ptr<Junction> const &source,shared_ptr<Junction>const & target, int duration);
    void printMap() const;
};

#endif //EX2_ROADMAP_H
