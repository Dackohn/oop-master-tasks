#ifndef GAS_STATION_H
#define GAS_STATION_H

#include "interfaces/Refuelable.h"
#include <iostream>

class GasStation : public Refuelable {
public:
    void refuel(const int& carId) override {
        std::cout << "Refueling gas car " << carId << "." << std::endl;
    }
};

#endif