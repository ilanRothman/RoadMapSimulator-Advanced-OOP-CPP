#include "RoadMap.h"

void RoadMap::addEdge(shared_ptr<Junction> const &source,shared_ptr<Junction>const & target, int duration) {

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


void RoadMap::printMap() const{
  for( const auto& source : graph )
  {
    cout << "[ " << source.first->getName() << " ]";

    for ( const auto& secondPair : source.second)
      cout << " -> [ " << secondPair.first->getName()  << " : "  << secondPair.second << " ] ";

    cout << endl;
  }
}
