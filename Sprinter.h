
#ifndef EX2_SPRINTER_H
#define EX2_SPRINTER_H

#include "Vehicle.h"
/**
 * Derived class from vehicle.
 * no need for greatest five since default are good enoght.
 * */
class Sprinter : public Vehicle{
private:
public:
    Sprinter(int st = 3): Vehicle(st){}

    virtual ~Sprinter() {
    }
};


#endif //EX2_SPRINTER_H
