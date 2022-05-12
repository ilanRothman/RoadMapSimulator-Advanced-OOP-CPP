#ifndef EX2_JUNCTION_H
#define EX2_JUNCTION_H
#include <string>
using namespace std;
class Junction{
    private:
        string name;
        int transTime;
    public:
        Junction(string&  name, int tTime ) : transTime(tTime), name(name) {};

        void setName(const string &name);

        //getters and setters.
        int getTransTime() const { return transTime;}
        void setTransTime(int transTime) { Junction::transTime = transTime;}
        const string &getName() const;
};

const std::string &Junction::getName() const {
    return name;
}

void Junction::setName(const string &name) {
    Junction::name = name;
}

#endif //EX2_JUNCTION_H
