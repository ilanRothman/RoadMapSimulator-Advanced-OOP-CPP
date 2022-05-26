
#include "Vehicle.h"

using namespace std;

#include "queue"


void Vehicle::printMap() const{
  for( const auto& source : graph )
  {
    cout << "[ " << source.first->getName() << " ]";

    for ( const auto& secondPair : source.second)
      cout << " -> [ " << secondPair.first->getName()  << " : "  << secondPair.second << " ] ";

    cout << endl;
  }
}

void Vehicle::BFS(const string &juncName,const graphMap& gr) const{

  juncPtr src = getSource(juncName);
  string name;
  bool printed = false;
  if(!src) {
    cout << juncName << " does not exist in the current network. \n";
    return;
  }

  map< string,bool > visited;
  list< string > queue;

  for ( const auto& i: gr ){
    visited.insert({i.first->getName(), false});
  }

  visited.at(juncName) = true;
  queue.push_back(src->getName());
  while(!queue.empty()){

    name = queue.front();
    queue.pop_front();

    for(const auto& adj: gr.at(getSource(name)))
    {
      if(visited.at(adj.first->getName())){
          continue;
      }
      printed = true;
      cout << adj.first->getName() << "\t";
      visited.at(adj.first->getName()) = true;
      queue.push_back(adj.first->getName());
    }
  }
  cout << endl;
  if(!printed)
    cout << juncName << " does not exist in the current network. \n";
}

juncPtr Vehicle::getSource(const string &source) const{
  for( const auto& i : graph )
    if( i.first->getName() == source )
      return i.first;
  return nullptr;
}

void Vehicle::updateTurnedGraph() {
  //creating all sources for turned graph.
  for(const auto & key:graph){
      vector<pair<juncPtr ,int > >p; // vector val.
      this->turnedGraph.insert(make_pair(key.first,p));
  }
  for(const auto& key:graph)
  {
      for(const auto& vec: key.second )
    {
          pair<juncPtr ,int> newPair = make_pair(key.first,vec.second);

          this->turnedGraph.at(getSource(vec.first->getName())).emplace_back(newPair);
    }
  }
}

const graphMap &Vehicle::getGraph() const {
    return graph;
}

const graphMap &Vehicle::getTurnedGraph() const {
    return turnedGraph;
}

void Vehicle::dijkstra(const string &source, const string &target) {
    auto cmp = [](const juncDist& lhs, const juncDist& rhs)
    {
        return lhs->second > rhs->second;
    };

    priority_queue <juncDist,vector<juncDist >, decltype(cmp) > minHeap(cmp);

    map <string,juncDist > distances;
    juncDist ptr;

    for(const auto& junc : graph){ // insert all junctions
        ptr = make_shared<pair<string,int> >(junc.first->getName(),INT32_MAX);
        minHeap.push(ptr);
        distances.insert({ptr->first,ptr});
    }

    if(distances.find(source) == distances.end() || distances.find(target) == distances.end())
    {
        cout << "route unavailable\n";
        return;
    }

    ptr = distances.at(source);
    ptr->second = 0;
    while(!minHeap.empty()){
        for(const auto& adj : getAdj(ptr->first)){
            if(distances.at(adj.first->getName())->second > adj.second + ptr->second + stopTime){
                distances.at(adj.first->getName())->second = adj.second + ptr->second + stopTime;
            }
        }
        minHeap.pop();
        ptr = minHeap.top();

    }
    if(distances.at(target)->second == INT32_MAX){
        cout << "route unavailable\n";
        return;
    }
    cout<< distances.at(target)->second - stopTime << endl;

}

const vecJI &Vehicle::getAdj(string &source) {

    return graph.at(getSource(source));
}

void Vehicle::updateTargetInGraph(juncPtr const& target)
{
  if(!getSource(target->getName()) ) // if target isn't in graph yet.
  {
    graph.insert({target,vecJI()});
  }
}

void Vehicle::addEdge(shared_ptr<Junction>const& source,shared_ptr<Junction>const& target, int duration) {

  updateTargetInGraph(target);

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
  vecJI v = {nTargetPair};
  graph.insert({source,v});
}



