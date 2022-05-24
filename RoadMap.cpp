#include "RoadMap.h"

#include <utility>
#include <queue>

RoadMap::RoadMap():graph() {
}

RoadMap::Edge::Edge(const string &source, const string &target, int duration, char type)
:source(source), dest(target), duration(duration),type(type) {}

void RoadMap::addEdge(juncPtr  const &source,juncPtr const &target, int duration,const char& type, map<char,int> &stopTimes) {
    if(!juncExists(source)){//check if source exist.
        makeVertices(source);
    }
    
    if(!juncExists(target)){ // check if target exist.
      makeVertices(target);
    }
  printMap();

    if(!checkEdgeExist(source,target)){ // checks if edges exists
      createEdges(source,target,stopTimes);
    }
  printMap();

    updateEdges(source,target,duration,type,stopTimes);
}

void RoadMap::printMap() const{
  for( const auto& source : graph )
  {
    cout << "[ " << source.first.first->getName() << " type : "<< source.first.second << " ]";

    for ( const auto& secondPair : source.second) {
        cout << " -> [ " << secondPair->getSource() << secondPair->getDest() << " : " << ( secondPair->getDuration() == INT32_MAX ? -1 : secondPair->getDuration() )
        << " type : " << secondPair->getType() << " ] ";
    }
    cout << endl;
  }
}

juncPtr RoadMap::getSource(const string &source) const {
    for( const auto& i : graph )
        if( i.first.first->getName() == source )
            return i.first.first;
    return nullptr;
}

int RoadMap::Edge::getDuration() const {
    return duration;
}

const char &RoadMap::Edge::getType() const {
    return type;
}

void RoadMap::Edge::setDuration(int dur) {
    Edge::duration = dur;
}

const string &RoadMap::Edge::getDest() const {
    return dest;
}

const string &RoadMap::Edge::getSource() const {
  return source;
}

// NOTICE - deleted parameter char type
bool RoadMap::juncExists(juncPtr const &source) {

  for (auto const &src : graph)
    if(src.first.first->getName() == source->getName())
      return true;
  return false;

}

void RoadMap::makeVertices(const juncPtr  &junc) {
    pair<juncPtr ,char> newJunc;
    vector<char> types = {'b','t','r','s'};
    for(char type : types){
        newJunc = make_pair(junc,type);
        graph.insert(make_pair(newJunc,vecEdge()));
    }
}

void RoadMap::updateEdges(const juncPtr  &source, const juncPtr  &target, int duration,
                          const char &type , map<char,int> &stopsTimes) {
    int transit = getSource(target->getName())->getTransTime();

    for(const auto& adj: getTargetVector(source))
    {
        if(adj->getDest() == target->getName())
        {
            if(adj->getType() == type) {
                if (adj->getDuration() > duration + stopsTimes.at(type)) {
                    adj->setDuration(duration + stopsTimes.at(type));
                }
                continue;
            }
            if (adj->getDuration() > duration + transit) {
                adj->setDuration(duration + transit);
            }
        }
    }
}

bool RoadMap::checkEdgeExist(const juncPtr  &source, const juncPtr  &target) {

    // going through all source edges, checking if already connected by edge to target
    for(const auto& adj: getTargetVector(source))
        if(adj->getDest() == target->getName())
            return true;
    return false;
}

void RoadMap::createEdges(const juncPtr  &source, const juncPtr  &target, map<char,int> &stopTimes){
    vector<char> types = {'b','r','t','s'};

    for(char t : types)
        connectEdges(source,target->getName(),t,stopTimes);
}

void RoadMap::connectEdges(const juncPtr & source,const string& target,char& type, map<char,int> &stopTimes) {

    if(type == 't') {
      getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(), target, stopTimes.at('t'), 't')));
    }
    
    else {
      getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(), target, INT32_MAX, 't')));
    }
    
    if(type == 's'){
      getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(),target,stopTimes.at('s'),'s')));
     }
    
    else{
      getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'s')));
  }
    
   if(type == 'r'){
     getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'r')));
   }
   
   else{
     getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(),target,stopTimes.at('r'),'r')));}
   
   if(type == 'b'){
      getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(),target,stopTimes.at('b'),'b')));
   }
   else{
     getTargetVector(source).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'b')));
   }
}

void RoadMap::dijkstra(const string &source, const string &target , map<char,int> &stopTimes) {

    auto cmp = [](const juncPtrType &lhs, const juncPtrType &rhs) {
        return lhs->second > rhs->second;
    };

    int min = INT32_MAX;
    vector<char> types = {'t','s','r','b'};
    priority_queue<juncPtrType, vector<juncPtrType >, decltype(cmp)> minHeap(cmp);

    map< pair<string,char> , juncPtrType > distances;
    juncPtrType ptr;

    for (const auto& junc: graph) { // insert all junctions
        ptr = make_shared<pair< pair<string, int>,char> >(make_pair(make_pair(junc.first.first->getName(),junc.first.second), INT32_MAX));
        minHeap.push(ptr);
        distances.insert({ptr->first, ptr});
    }

    if (!juncExists(getSource(source))) {
        cout << "route unavailable\n";
        return;
    }

    for(char type : types){
        distances.at({source,type})->first.second = 0;
    }
    ptr = distances.at({source,'b'});
//    int stopTime = 0;

    while (!minHeap.empty()) {
        for (const auto &adj: getAdj(ptr)) {
//          if(ptr->second == adj->getType()){
//            stopTime = stopTimes.at(ptr->second);
//          }
            if (distances.at({adj->getDest(),ptr->second })->first.second > adj->getDuration() + ptr->first.second ) {
                distances.at({adj->getDest(),ptr->second })->first.second  = adj->getDuration() + ptr->first.second ;
            }
        }
        minHeap.pop();
        ptr = minHeap.top();
    }

    for(char type : types){
        if( min < distances.at({target,type})->first.second)
            min = distances.at({target,type})->first.second;
    }

    min < INT32_MAX ? cout << min << endl : cout << "route unavailable\n";
}

RoadMap::vecEdge &RoadMap::getAdj(juncPtrType& ptr) {
    return graph.at({getSource(ptr->first.first),ptr->second});
}

//ONLY USE IF TARGET VEC EXISTS
RoadMap::vecEdge &RoadMap::getTargetVector(const juncPtr &source) {
  for( auto& i : graph )
    if(i.first.first->getName() == source->getName())
      return i.second;
}








