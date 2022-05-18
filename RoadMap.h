#ifndef EX2_ROADMAP_H
#define EX2_ROADMAP_H
#include "Junction/Junction.h"
#include "Vehicle/Vehicle.h"
#include "map"


using namespace std;

class RoadMap{
    class Edge{
        private:
            const string& source;
            const string &dest;
            int duration;
            string type;
        public:
            Edge(const string& source, const string& target, int duration, string type);

        const string &getSource() const;

        const string &getDest() const;

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
