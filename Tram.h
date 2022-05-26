#ifndef EX2_TRAM_H
#define EX2_TRAM_H

#include "Vehicle.h"
/**
 * Derived class from vehicle.
 * no need for greatest five since default are good enoght.
 * */
class Tram : public Vehicle{
public:
    Tram(int st = 2): Vehicle(st){};

    virtual ~Tram() {
    }

};


#endif //EX2_TRAM_H
