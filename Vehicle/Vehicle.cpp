//
// Created by iroth on 5/11/2022.
//

#include "Vehicle.h"


void Vehicle::addEdge(shared_ptr<Junction>const& source,shared_ptr<Junction>const& target, int duration) {
    auto value = graph.find(source);

    if( value != graph.end()) // Source junction found
    {
        for ( auto trg : value->second ) // going through all Target Junctions
           if( trg.first->getName() == target->getName() ) // There's already an edge
               if ( trg.second > duration )
               {
                   trg.second = duration;
                   return;
               }
        // target hasn't been found
        value->second.emplace_back(target,duration);
    }
    // Source doesn't exists
    auto nTargetPair = std::make_pair(target,duration);
    vector < pair < shared_ptr<Junction> ,int> > v = {nTargetPair};
    graph.insert({source,v});
}

void Vehicle::printMap(){
}
