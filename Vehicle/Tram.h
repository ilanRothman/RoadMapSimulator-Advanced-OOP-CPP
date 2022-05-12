#ifndef EX2_TRAM_H
#define EX2_TRAM_H

#include "Vehicle.h"

class Tram : public Vehicle{
public:
    Tram(int st = 2): Vehicle(st){};

    virtual ~Tram() {
    }

};


#endif //EX2_TRAM_H
