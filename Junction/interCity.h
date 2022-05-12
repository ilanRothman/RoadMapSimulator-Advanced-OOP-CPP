#ifndef EX2_INTERCITY_H
#define EX2_INTERCITY_H
#include "Junction.h"
class InterCity : public Junction{
    public:
        InterCity(int Ttime = 15) : Junction(Ttime){};
};
#endif //EX2_INTERCITY_H
