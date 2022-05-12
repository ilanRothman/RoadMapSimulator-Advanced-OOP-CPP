
#ifndef EX2_BUS_H
#define EX2_BUS_H

#include <memory>
#include "Vehicle.h"

class Bus : public Vehicle{
public:
    Bus(int st = 1): Vehicle(st){};
    virtual ~Bus() {
    }

};


#endif //EX2_BUS_H
