#include "../src/RobotDinner.h"
#include "../src/PeopleDinner.h"
#include <cassert>
#include <iostream>
#include <string>

void testDineable() {
    PeopleDinner peopleDinner;
    RobotDinner robotDinner;

    std::cout << "Running tests..." << std::endl;

    peopleDinner.serveDinner(1);
    robotDinner.serveDinner(2);


    std::cout << "Tests completed!" << std::endl;
}
