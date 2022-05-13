#include "RoadMap.h"

void RoadMap::addEdge(shared_ptr<Junction> const &source,shared_ptr<Junction>const & target, int duration) {
    auto value = this->graph.find(source); //checking if src is in graph already.
    if(value != graph.end()){ // if found
        for(auto dest : value->second){ // searching for target.
            if(dest.first->getName() == target->getName()){ // found.
                if(dest.second > duration){
                    dest.second = duration; // updating if needed
                    return;
                }
            }
        }
        value->second.emplace_back(make_pair(target,duration)); // target not found.
    }
    auto nTargetPair = make_pair(target,duration);
    vector < pair < shared_ptr<Junction> ,int> > v = {nTargetPair};
    graph.insert({source,v});
}
