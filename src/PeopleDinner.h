#ifndef PEOPLE_DINNER_H
#define PEOPLE_DINNER_H

#include "interfaces/Dineable.h"
#include <iostream>

class PeopleDinner : public Dineable {
public:
    void serveDinner(const int& carId) override {
        std::cout << "Serving dinner to people in car " << carId << "." << std::endl;
    }
};

#endif