#ifndef EX2_ROADMAP_H
#define EX2_ROADMAP_H
#include "Junction/Junction.h"
#include "Vehicle/Vehicle.h"

using namespace std;

class RoadMap{
private:
    vector< pair <Junction*, vector< pair< Junction*, int> > > > graph;

public:
};

#endif //EX2_ROADMAP_H
