#ifndef EX2_CENTRAL_H
#define EX2_CENTRAL_H
#include "Junction.h"
class Central : public Junction{
    public:
        Central(int Ttime = 10): Junction(Ttime){};
};
#endif //EX2_CENTRAL_H
