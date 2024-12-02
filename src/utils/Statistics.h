#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>

class Statistics {
private:
    int electricCars = 0;
    int gasCars = 0;
    int peopleServed = 0;
    int robotsServed = 0;
    int totalElectricConsumption = 0;
    int totalGasConsumption = 0;
    int diningCars = 0;
    int notDiningCars = 0;

public:
    void incrementElectricCars() { electricCars++; }
    void incrementGasCars() { gasCars++; }
    void incrementPeopleServed() { peopleServed++; }
    void incrementRobotsServed() { robotsServed++; }

    void addElectricConsumption(int consumption) { totalElectricConsumption += consumption; }
    void addGasConsumption(int consumption) { totalGasConsumption += consumption; }

    void incrementDiningCars() { diningCars++; }
    void incrementNotDiningCars() { notDiningCars++; }

    // Getter methods
    int electricCarsCount() const { return electricCars; }
    int gasCarsCount() const { return gasCars; }
    int peopleServedCount() const { return peopleServed; }
    int robotsServedCount() const { return robotsServed; }
    int electricConsumption() const { return totalElectricConsumption; }
    int gasConsumption() const { return totalGasConsumption; }
    int diningCarsCount() const { return diningCars; }
    int notDiningCarsCount() const { return notDiningCars; }

    void printStats() const {
        std::cout << "{"
                  << "\"ELECTRIC\": " << electricCars << ", "
                  << "\"GAS\": " << gasCars << ", "
                  << "\"PEOPLE\": " << peopleServed << ", "
                  << "\"ROBOTS\": " << robotsServed << ", "
                  << "\"DINING\": " << diningCars << ", "
                  << "\"NOT_DINING\": " << notDiningCars << ", "
                  << "\"CONSUMPTION\": {"
                  << "\"ELECTRIC\": " << totalElectricConsumption << ", "
                  << "\"GAS\": " << totalGasConsumption
                  << "}"
                  << "}" << std::endl;
    }
};

#endif
