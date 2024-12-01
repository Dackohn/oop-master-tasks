#include "../src/GasStation.h"
#include "../src/ElectricStation.h"
#include <cassert>
#include <iostream>
#include <string>

void testRefuelable() {
    ElectricStation electricStation;
    GasStation gasStation;

    std::cout << "Running tests..." << std::endl;


    electricStation.refuel("TestCar3");
    gasStation.refuel("TestCar4");

    std::cout << "Tests completed!" << std::endl;
}
