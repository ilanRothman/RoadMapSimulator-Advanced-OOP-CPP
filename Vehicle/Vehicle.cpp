
#include "Vehicle.h"

using namespace std;

void Vehicle::addEdge(shared_ptr<Junction>const& source,shared_ptr<Junction>const& target, int duration) {
  if( !getSource(target->getName()) ){ // if target isn't in graph yet.
    graph.insert({target,vector < pair < shared_ptr<Junction> ,int> >()});
  }
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

  shared_ptr<Junction> src = getSource(juncName);

  if(!src) {
    cout << juncName << " does not exist in the current network. \n";
    return;
  }

  map< string,bool > visited;
  list< shared_ptr<Junction> > queue;

  for ( const auto& i: gr ){
    visited.insert({i.first->getName(), false});
  }

  visited.at(juncName) = true;
  queue.push_back(src);
  while(!queue.empty()){

    src = queue.front();
    queue.pop_front();

    for(const auto& adj: gr.at(src))
    {
      if(visited.at(adj.first->getName())){
          continue;
      }

      cout << adj.first->getName() << "\t";
      visited.at(adj.first->getName()) = true;
      queue.push_back(adj.first);
    }
  }
}

shared_ptr<Junction> Vehicle::getSource(const string &source) const{
  for( const auto& i : graph )
    if( i.first->getName() == source )
      return i.first;
  return nullptr;
}

//void Vehicle::DFS(const string &source,const string &target, map<string, bool> &visited, bool &toPrint) {
//  if( source == target )
//  {
//    toPrint = true;
//    return;
//  }
//  visited.at(source) = true;
//  for ( const auto& i : graph.at(getSource(source)) )
//  {
//    if( !visited.at(i.first->getName()) )
//    {
//      DFS(i.first->getName(),target,visited,toPrint);
//      if( toPrint ) {
//        cout << "[ " <<  source << " ]";
////        return;
//      }
//    }
//  }
//}
//
//void Vehicle::dfsHelper(const string& target){
//  map<string,bool> visited;
//  bool toPrint = false;
//  bool printed = false;
//
//  for(const auto& i: graph)
//    visited.insert({i.first->getName(),false});
//
//  for(const auto& i: visited)
//  {
//    if( !i.second )
//    {
//      DFS(i.first,target,visited,toPrint);
//    }
//    if( toPrint )
//      printed = true;
//
//    toPrint = false;
//  }
//
//  if(!printed)
//    cout << "NO ROADS AT ALL";
//
//}

void Vehicle::UpdateTurnedGraph() {
  //creating all sources for turned graph.
  for(const auto & key:graph){
      vector<pair<shared_ptr<Junction>,int > >p; // vector val.
      this->turnedGraph.insert(make_pair(key.first,p));
  }
  for(const auto& key:graph)
  {
      for(const auto& vec: key.second )
    {
          pair<shared_ptr<Junction>,int> newPair = make_pair(vec.first,vec.second);
          this->turnedGraph.at(vec.first).emplace_back(newPair);
    }
  }
}

const graphMap &Vehicle::getGraph() const {
    return graph;
}

const graphMap &Vehicle::getTurnedGraph() const {
    return turnedGraph;
}

