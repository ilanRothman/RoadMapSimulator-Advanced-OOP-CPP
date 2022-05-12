#include "RoadMap.h"

void RoadMap::addEdge(shared_ptr<Junction> const &source,shared_ptr<Junction>const & target, int duration) {
    auto value = this->graph.find(source);
    if(value != graph.end()){
        for(auto dest : value->second){
            if(dest.first->getName() == target->getName()){
                if(dest.second > duration){
                    dest.second = duration;
                    return;
                }
            }
        }
        value->second.emplace_back(make_pair(target,duration));
    }
    this->graph.insert((source,make_pair(target,duration)));

}
