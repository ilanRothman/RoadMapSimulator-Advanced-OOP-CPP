#ifndef EX2_ROADMAP_H
#define EX2_ROADMAP_H
#include "Junction/Junction.h"
#include "Vehicle/Vehicle.h"
#include "map"


using namespace std;

class RoadMap{
    class Edge{
        private:
            shared_ptr<Junction> const &source;
            shared_ptr<Junction> const &dest;
            int duration;
            string type;
        public:
            Edge(const shared_ptr<Junction> &source, const shared_ptr<Junction> &dest, int duration, string type);

            const shared_ptr<Junction> &getSource() const;

            const shared_ptr<Junction> &getDest() const;

            int getDuration() const;

            void setDuration(int dur);

            const string &getType() const;

    };
private:
    map <shared_ptr<Junction> , vector<shared_ptr<Edge>> > graph;

public:
    void addEdge(shared_ptr<Junction> const &source,shared_ptr<Junction>const & target, int duration,const string& type);
    void printMap() const;
};

#endif //EX2_ROADMAP_H
