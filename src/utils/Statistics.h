#ifndef STATISTICS_H
#define STATISTICS_H

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

    int electricCarsCount() const { return electricCars; }
    int gasCarsCount() const { return gasCars; }
    int peopleServedCount() const { return peopleServed; }
    int robotsServedCount() const { return robotsServed; }

    void printStats() const {
        std::cout << "Electric cars served: " << electricCars << std::endl;
        std::cout << "Gas cars served: " << gasCars << std::endl;
        std::cout << "People served dinner: " << peopleServed << std::endl;
        std::cout << "Robots served dinner: " << robotsServed << std::endl;
    }
};

#endif
