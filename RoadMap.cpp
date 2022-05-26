#include "RoadMap.h"

#include <utility>
#include <queue>
#define INF INT32_MAX/2



RoadMap::Edge::Edge(const string &source, const string &target, int duration, char type)
:source(source), dest(target), duration(duration),type(type) {}

void RoadMap::addEdge(juncPtr  const &source,juncPtr const &target, int duration,const char& type, map<char,int> &stopTimes) {
    if(!juncExists(source)){//check if source exist.
        makeVertices(source);
    }
    
    if(!juncExists(target)){ // check if target exist.
      makeVertices(target);
    }

    if(!checkEdgeExist(source,target,type)){ // checks if edges exists
      createEdges(source,target,stopTimes);
    }


    updateEdges(source,target,duration,type,stopTimes);
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



// NOTICE - deleted parameter char type
bool RoadMap::juncExists(juncPtr const &source) {
    if(source == nullptr)
        return false;
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

    for(const auto& adj: getTargetVector(source,type))
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

bool RoadMap::checkEdgeExist(const juncPtr  &source, const juncPtr  &target, char type) {

    // going through all source edges, checking if already connected by edge to target
    for(const auto& adj: getTargetVector(source,type))
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

    getTargetVector(source,type).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INF,'t')));
    getTargetVector(source,type).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INF,'s')));
    getTargetVector(source,type).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INF,'b')));
    getTargetVector(source,type).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INF,'r')));
}

void RoadMap::dijkstra(const string &source, const string &target , map<char,int> &stopTimes) {

    auto cmp = [](const juncPtrType &lhs, const juncPtrType &rhs) {
        return lhs->first.second > rhs->first.second;
    };

    int min = INF;
    char lastType;
    vector<char> types = {'t','s','r','b'};
    priority_queue<juncPtrType, vector<juncPtrType >, decltype(cmp)> minHeap(cmp);

    map< pair<string,char> , juncPtrType > distances;
    juncPtrType ptr;

    for (const auto& junc: graph) { // insert all junctions
        ptr = make_shared<pair< pair<string, int>,char> >(make_pair(make_pair(junc.first.first->getName(),INF),junc.first.second ));
        if(ptr->first.first == source){
            ptr->first.second = 0;
        }
        minHeap.push(ptr);
        distances.insert({make_pair(junc.first.first->getName(),junc.first.second), ptr});
    }

    if (!juncExists(getSource(source))) {
        cout << "route unavailable\n";
        return;
    }
    ptr = minHeap.top();

    while (!minHeap.empty()) {
//        cout <<"source: " <<ptr->first.first << "type: "<< ptr->second << " \n" ;
        for (const auto &adj: getAdj(ptr)) {
            if (distances.at({adj->getDest(),adj->getType() })->first.second > adj->getDuration() + ptr->first.second ) {
                distances.at({adj->getDest(),adj->getType() })->first.second  = adj->getDuration() + ptr->first.second;

            }

        }
//        cout << distances.at({ptr->first.first,ptr->second })->first.second << endl;
        minHeap.pop();
        ptr = minHeap.top();
    }

    for(char type : types){
        if( min > distances.at({target,type})->first.second){
            min = distances.at({target, type})->first.second;
            lastType = type;
        }

    }
    min < INF  ? (cout << min - stopTimes.at(lastType) << endl) : (cout << "route unavailable\n");
}

RoadMap::vecEdge &RoadMap::getAdj(juncPtrType& ptr) {
    return getTargetVector(getSource(ptr->first.first),ptr->second);
}

//ONLY USE IF TARGET VEC EXISTS
RoadMap::vecEdge &RoadMap::getTargetVector(const juncPtr &source, char type) {
  for( auto& i : graph )
    if((i.first.first->getName() == source->getName() ) && (i.first.second == type))
      return i.second;
    return vecEdge() = {};
}










