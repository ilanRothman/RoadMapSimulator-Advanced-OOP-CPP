
#ifndef EX2_RAIL_H
#define EX2_RAIL_H

#include "Vehicle.h"

class Rail: public Vehicle{
    public:
        Rail(int st = 5): Vehicle(st){};

    virtual ~Rail() {
    }
};


#endif //EX2_RAIL_H
