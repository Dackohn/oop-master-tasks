#ifndef ROBOT_DINNER_H
#define ROBOT_DINNER_H

#include "interfaces/Dineable.h"
#include <iostream>

class RobotDinner : public Dineable {
public:
    void serveDinner(const std::string& carId) override {
        std::cout << "Serving dinner to robots in car " << carId << "." << std::endl;
    }
};

#endif