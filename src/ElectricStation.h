#ifndef ELECTRIC_STATION_H
#define ELECTRIC_STATION_H

#include "interfaces/Refuelable.h"
#include <iostream>

class ElectricStation : public Refuelable {
public:
    void refuel(const std::string& carId) override {
        std::cout << "Refueling electric car " << carId << "." << std::endl;
    }
};

#endif