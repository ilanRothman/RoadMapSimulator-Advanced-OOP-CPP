#ifndef EX2_JUNCTION_H
#define EX2_JUNCTION_H
#include <string>
using namespace std;

/**
 * Junction object
 * We had no need to implement the Big 5 since we could rely on the default ones for our needs.
 * */
class Junction {
private:
    string name;
    int transTime; // transit time.
public:
    /*
     * constructor which gets the name and the transit time of the Junction.
     * */
    Junction(string &name, int tTime) : transTime(tTime), name(name) {};

    /*
     * getters and setters.
     */
    int getTransTime() const { return transTime; }

    const string &getName() const { return this->name; };

};
#endif //EX2_JUNCTION_H
