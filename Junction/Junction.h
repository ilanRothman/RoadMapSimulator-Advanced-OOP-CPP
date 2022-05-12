#ifndef EX2_JUNCTION_H
#define EX2_JUNCTION_H

class Junction{
    private:
        int transTime;
    public:
        Junction(int tTime) : transTime(tTime){};
        virtual ~Junction() = 0; // abstract.

        //getters and setters.
        int getTransTime() const { return transTime;}
        void setTransTime(int transTime) { Junction::transTime = transTime;}
};
#endif //EX2_JUNCTION_H
