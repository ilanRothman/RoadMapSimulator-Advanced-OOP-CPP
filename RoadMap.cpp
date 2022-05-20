#include "RoadMap.h"

#include <utility>
#include <queue>

void RoadMap::addEdge(shared_ptr<Junction> const &source,shared_ptr<Junction>const &target, int duration,const char& type) {
    if(!juncExists(source,type)){//check if source exist.
        makeVertices(source);
    }
    if(!juncExists(target,type)){ // check if target exist.
        makeVertices(target);
    }
    if(!checkEdgeExist(source,target)){ // checks if edges exists
        createEdges(source,target);
    }

    updateEdges(source,target,duration,type);
}


//void RoadMap::printMap() const{
//  for( const auto& source : graph )
//  {
//    cout << "[ " << source.first->getName() << " ]";
//
//    for ( const auto& secondPair : source.second) {
//        cout << " -> [ " << secondPair->getDest() << " : " << secondPair->getDuration() << " ] ";
//    }
//    cout << endl;
//  }
//}

shared_ptr<Junction> RoadMap::getSource(const string &source) const {
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

const string &RoadMap::Edge::getSource() const {
    return source;
}

const string &RoadMap::Edge::getDest() const {
    return dest;
}

bool RoadMap::juncExists(shared_ptr<Junction> const &source, const char &type) {
    return graph.find(std::make_pair(source,type)) != graph.end();
}

void RoadMap::makeVertices(const shared_ptr<Junction> &junc) {
    pair<shared_ptr<Junction>,char> newJunc;
    vector<char> types = {'b','t','r','s'};
    for(char type : types){
        newJunc = make_pair(junc,type);
        graph.insert(make_pair(newJunc,vector<shared_ptr<Edge> >()));
    }
}

void RoadMap::updateEdges(const shared_ptr<Junction> &source, const shared_ptr<Junction> &target, int duration,
                          const char &type) {
    int transit = getSource(target->getName())->getTransTime();
    for(const auto& adj:graph.at({source,type}))
    {
        if(adj->getDest() == target->getName())
        {
            if(adj->getType() == type) {
                if (adj->getDuration() > duration) {
                    adj->setDuration(duration);
                }
                continue;
            }
            if (adj->getDuration() > duration + transit) {
                adj->setDuration(duration + transit);
            }
        }
    }
}

bool RoadMap::checkEdgeExist(const shared_ptr<Junction> &source, const shared_ptr<Junction> &target) {
    // going through all source edges, checking if already connected by edge to target
    for(const auto& adj: graph.at(std::make_pair(source,'b'))){
        if(adj->getDest() == target->getName()){
            return true;
        }
    }
    return false;
}

void RoadMap::createEdges(const shared_ptr<Junction> &source, const shared_ptr<Junction> &target){
    vector<char> types = {'b','r','t','s'};

    for(char t : types)
        connectEdges(source,target->getName(),t);

}

void RoadMap::connectEdges(const shared_ptr<Junction>& source,const string& target,char& type) {
    graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'t')));
    graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'s')));
    graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'b')));
    graph.at({source,type}).emplace_back(make_shared<Edge>(Edge(source->getName(),target,INT32_MAX,'r')));
}

void RoadMap::dijkstra(const string &source, const string &target) {
    auto cmp = [](const shared_ptr<pair< pair<string, int>,char> > &lhs, const shared_ptr<pair< pair<string, int>,char> > &rhs) {
        return lhs->second > rhs->second;
    };
    int min = INT32_MAX;
    vector<char> types = {'t','s','r','b'};
    priority_queue<shared_ptr<pair< pair<string, int>,char> >, vector<shared_ptr<pair< pair<string, int>,char> > >, decltype(cmp)> minHeap(cmp);

    map< pair<string,char> , shared_ptr<pair< pair<string, int>,char > > > distances;
    shared_ptr<pair< pair<string, int>,char> > ptr;

    for (const auto& junc: graph) { // insert all junctions
        ptr = make_shared<pair< pair<string, int>,char> >(make_pair(make_pair(junc.first.first->getName(),junc.first.second), INT32_MAX));
        minHeap.push(ptr);
        distances.insert({ptr->first, ptr});
    }

    if (!juncExists(getSource(source),'b')) {
        cout << "route unavailable\n";
        return;
    }

    for(char type : types){
        distances.at({source,type})->first.second = 0;
    }
    ptr = distances.at({source,'b'});

    while (!minHeap.empty()) {
        for (const auto &adj: getAdj(ptr)) {
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

vector< shared_ptr<RoadMap::Edge> > &RoadMap::getAdj(shared_ptr<pair< pair<string, int>,char> >& ptr) {
    return graph.at({getSource(ptr->first.first),ptr->second});
}

RoadMap::RoadMap():graph() {

}








