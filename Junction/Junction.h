#ifndef EX2_JUNCTION_H
#define EX2_JUNCTION_H
#include <string>
using namespace std;
class Junction {
private:
    string name;
    int transTime;
public:
    Junction(string &name, int tTime) : transTime(tTime), name(name) {};

    //getters and setters.
    int getTransTime() const { return transTime; }

    void setTransTime(int transTime) { this->transTime = transTime; }

    const string &getName() const { return this->name; };

    void setName(const string &name) { this->name = name; };

};
#endif //EX2_JUNCTION_H
