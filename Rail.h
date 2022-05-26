
#ifndef EX2_RAIL_H
#define EX2_RAIL_H

#include "Vehicle.h"
/**
 * Derived class from vehicle.
 * no need for greatest five since default are good enoght.
 * */
class Rail: public Vehicle{
    public:
        Rail(int st = 5): Vehicle(st){};

    virtual ~Rail() {
    }
};


#endif //EX2_RAIL_H
