
#ifndef EX2_SPRINTER_H
#define EX2_SPRINTER_H

#include "Vehicle.h"

class Sprinter : public Vehicle{
private:
    int StopTime;
public:
    Sprinter(int st = 3): Vehicle(st){}

};


#endif //EX2_SPRINTER_H
