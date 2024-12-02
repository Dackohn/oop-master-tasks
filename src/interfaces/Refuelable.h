#ifndef REFUELABLE_H
#define REFUELABLE_H

#include <string>

class Refuelable {
public:
    virtual void refuel(const int& carId) = 0;
    virtual ~Refuelable() = default;
};

#endif
