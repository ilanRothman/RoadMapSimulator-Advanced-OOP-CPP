#include "RoadMap.h"

#include <utility>

void RoadMap::addEdge(shared_ptr<Junction> const &source,shared_ptr<Junction>const &target, int duration,const string& type) {

  // check if source exists
  for(auto& src : graph) {

    if (src.first->getName() == source->getName()) {
      for (auto& trg: src.second) // going through all Target Junctions
      {
          if (trg->getDest() == target->getName() && trg->getType() == type) { // There's already an edge
              if (trg->getDuration() > duration) {
                  trg->setDuration(duration);
                  return;
              }
          }
      }
      shared_ptr<Edge> edge = make_shared<Edge>(source->getName(),target->getName(),duration,type);
      src.second.emplace_back(edge);
      return;
    }
  }
  // Source doesn't exists
  shared_ptr<Edge> edge = make_shared<Edge>(source->getName(),target->getName(),duration,type);
  vector <shared_ptr<Edge> > v = {edge};
  graph.insert({source,v});

}


void RoadMap::printMap() const{
  for( const auto& source : graph )
  {
    cout << "[ " << source.first->getName() << " ]";

    for ( const auto& secondPair : source.second) {
        cout << " -> [ " << secondPair->getDest() << " : " << secondPair->getDuration() << " ] ";
    }
    cout << endl;
  }
}


int RoadMap::Edge::getDuration() const {
    return duration;
}

const string &RoadMap::Edge::getType() const {
    return type;
}

void RoadMap::Edge::setDuration(int dur) {
    Edge::duration = dur;
}

RoadMap::Edge::Edge(const string &source, const string &target, int duration, string type) : source(source), dest(target), duration(duration),type(type) {

}

const string &RoadMap::Edge::getSource() const {
    return source;
}

const string &RoadMap::Edge::getDest() const {
    return dest;
}







