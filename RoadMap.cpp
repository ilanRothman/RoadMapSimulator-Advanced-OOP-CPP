#include "RoadMap.h"

#include <utility>
#include <queue>

void RoadMap::addEdge(juncPtr  const &source,juncPtr const &target, int duration,const char& type, map<char,int> &stopTimes) {
    if(!juncExists(source)){//check if source exist.
        cout << "\n CHECK 1 - - JUNC " << source->getName() << " DOESNT EXISTS \n";
        makeVertices(source);
    }
    cout << "\n CHECK 1.5";
    cout.flush();

    if(!juncExists(target)){ // check if target exist.
      cout << "\n CHECK 2 - - JUNC " << target->getName() << " DOESNT EXISTS \n";
      makeVertices(target);
    }
  cout << "\n CHECK 2.5";

  cout.flush();

    if(!checkEdgeExist(source,target)){ // checks if edges exists
      cout << "\n CHECK 3 - - EDGE " << source->getName() << " :  " <<  target->getName() << " DOESNT EXISTS \n";
      cout.flush();

      createEdges(source,target,stopTimes);
    }

    updateEdges(source,target,duration,type,stopTimes);
}


void RoadMap::printMap() const{
  for( const auto& source : graph )
  {
    cout << "[ " << source.first.first->getName() << " type : "<< source.first.second << " ]";

    for ( const auto& secondPair : source.second) {
        cout << " -> [ " << secondPair->getDest() << " : " << ( secondPair->getDuration() == INT32_MAX ? -1 : secondPair->getDuration() ) << " type : " << secondPair->getType() << " ] ";
    }
    cout << endl;
  }
}

juncPtr  RoadMap::getSource(const string &source) const {
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

RoadMap::Edge::Edge(const string &source, const string &target, int duration, char type) : source(source), dest(target), duration(duration),type(type) {

}

const string &RoadMap::Edge::getDest() const {
    return dest;
}

// NOTICE - deleted parameter char type
bool RoadMap::juncExists(juncPtr const &source) {
  for (auto const &src : graph)
    if(src.first.first->getName() == source->getName())
    {
      cout << "\n IT ENTERED \n";
      cout.flush();
      return true;
    }
  return false;
//    return graph.find(std::make_pair(source,'b')) != graph.end();
}

void RoadMap::makeVertices(const juncPtr  &junc) {
    pair<juncPtr ,char> newJunc;
    vector<char> types = {'b','t','r','s'};
    for(char type : types){
        newJunc = make_pair(junc,type);
        graph.insert(make_pair(newJunc,vector<shared_ptr<Edge> >()));
    }
}

void RoadMap::updateEdges(const juncPtr  &source, const juncPtr  &target, int duration,
                          const char &type , map<char,int> &stopsTimes) {
    int transit = getSource(target->getName())->getTransTime();

    for(const auto& adj:graph.at({source,type}))
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

  cout << "\n CHECK 2.7";

  cout.flush();
    // going through all source edges, checking if already connected by edge to target
    for(const auto& adj: graph.at(std::make_pair(source,'b'))){
        if(adj->getDest() == target->getName()){
            return true;
        }
    }
    return false;
}

void RoadMap::createEdges(const juncPtr  &source, const juncPtr  &target, map<char,int> &stopTimes){
    vector<char> types = {'b','r','t','s'};

    for(char t : types)
        connectEdges(source,target->getName(),t,stopTimes);
}

void RoadMap::connectEdges(const juncPtr & source,const string& target,char& type, map<char,int> &stopTimes) {
    if(type == 't') {
      graph.at({source, type}).emplace_back(make_shared<Edge>(Edge(source->getName(), target, stopTimes.at('t'), 't')));
    }
    
    else {
      graph.at({source, type}).emplace_back(make_shared<Edge>(Edge(source->getName(), target, INT32_MAX, 't')));
    }
    
    if(type == 's'){
      graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,stopTimes.at('s'),'s')));
     }
    
    else{
      graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'s')));
  }
    
   if(type == 'r'){
     graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'r')));
   }
   
   else{
     graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,stopTimes.at('r'),'r')));}
   
   if(type == 'b'){
      graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,stopTimes.at('b'),'b')));
   }
   else{
     graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'b')));
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

vector< shared_ptr<RoadMap::Edge> > &RoadMap::getAdj(juncPtrType& ptr) {
    return graph.at({getSource(ptr->first.first),ptr->second});
}

RoadMap::RoadMap():graph() {

}








