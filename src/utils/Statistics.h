#ifndef STATS_H
#define STATS_H

#include <iostream>

class Statistics {
private:
    int electricCars = 0;
    int gasCars = 0;
    int peopleServed = 0;
    int robotsServed = 0;

public:
    void incrementElectricCars() { electricCars++; }
    void incrementGasCars() { gasCars++; }
    void incrementPeopleServed() { peopleServed++; }
    void incrementRobotsServed() { robotsServed++; }

    void printStats() const {
        std::cout << "Electric cars served: " << electricCars << std::endl;
        std::cout << "Gas cars served: " << gasCars << std::endl;
        std::cout << "People served dinner: " << peopleServed << std::endl;
        std::cout << "Robots served dinner: " << robotsServed << std::endl;
    }
};

#endif
