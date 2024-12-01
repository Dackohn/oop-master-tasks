#include "../src/RobotDinner.h"
#include "../src/PeopleDinner.h"
#include <cassert>
#include <iostream>
#include <string>

void testDineable() {
    PeopleDinner peopleDinner;
    RobotDinner robotDinner;

    std::cout << "Running tests..." << std::endl;

    peopleDinner.serveDinner("TestCar1");
    robotDinner.serveDinner("TestCar2");


    std::cout << "Tests completed!" << std::endl;
}
