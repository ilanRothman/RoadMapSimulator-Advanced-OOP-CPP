
#include "Vehicle.h"
using namespace std;

void Vehicle::addEdge(shared_ptr<Junction>const& source,shared_ptr<Junction>const& target, int duration) {
  if( !getSource(target->getName()) ){ // if target isn't in graph yet.
    graph.insert({target,vector < pair < shared_ptr<Junction> ,int> >()});
  }
  // check if source exists
    for(auto& src : graph) {

      if (src.first->getName() == source->getName()) {
        for (auto& trg: src.second) // going through all Target Junctions
        {
          if (trg.first->getName() == target->getName()) // There's already an edge
            if (trg.second > duration) {
              trg.second = duration;
              return;
            }
        }
        src.second.emplace_back(target, duration);
        return;
      }
    }
    // Source doesn't exists
    auto nTargetPair = std::make_pair(target,duration);
    vector < pair < shared_ptr<Junction> ,int> > v = {nTargetPair};
    graph.insert({source,v});

}

void Vehicle::printMap(){
}
