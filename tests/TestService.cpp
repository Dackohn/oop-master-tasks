#include "../src/CarStation.h"
#include "../src/interfaces/Queue.h"
#include "../src/utils/Statistics.h"
#include "../src/PeopleDinner.h"
#include "../src/ElectricStation.h"
#include "../src/GasStation.h"
#include "../src/LinkedListQueue.h"
#include <iostream>

void customAssert(bool condition, const std::string& errorMessage) {
    if (!condition) {
        std::cerr << "Test failed: " << errorMessage << std::endl;
        exit(EXIT_FAILURE);
    }
}

void testFullService() {
    Statistics stats;
    PeopleDinner peopleDinner;
    ElectricStation electricStation;
    LinkedListQueue<Car> queue;

    CarStation station(&peopleDinner, &electricStation, &queue, &stats);

    station.addCar(Car("1", CarType::ELECTRIC, PassengerType::PEOPLE, true));
    station.addCar(Car("2", CarType::GAS, PassengerType::ROBOTS, true));
    station.addCar(Car("3", CarType::ELECTRIC, PassengerType::PEOPLE, false));

    station.serveCars();

    customAssert(stats.electricCarsCount() == 2, "Incorrect number of electric cars served.");
    customAssert(stats.gasCarsCount() == 1, "Incorrect number of gas cars served.");
    customAssert(stats.peopleServedCount() == 1, "Incorrect number of people served dinner.");
    customAssert(stats.robotsServedCount() == 1, "Incorrect number of robots served dinner.");

    std::cout << "Test Full Service Passed!" << std::endl;
}

void testPartialService() {
    Statistics stats;
    PeopleDinner peopleDinner;
    GasStation gasStation;
    LinkedListQueue<Car> queue;

    CarStation station(&peopleDinner, &gasStation, &queue, &stats);

    station.addCar(Car("1", CarType::GAS, PassengerType::PEOPLE, false));
    station.addCar(Car("2", CarType::GAS, PassengerType::ROBOTS, true));

    station.serveCars();

    customAssert(stats.electricCarsCount() == 0, "Electric cars were incorrectly counted.");
    customAssert(stats.gasCarsCount() == 2, "Incorrect number of gas cars served.");
    customAssert(stats.peopleServedCount() == 0, "People were incorrectly served dinner.");
    customAssert(stats.robotsServedCount() == 1, "Incorrect number of robots served dinner.");

    std::cout << "Test Partial Service Passed!" << std::endl;
}

void testNoCars() {
    Statistics stats;
    PeopleDinner peopleDinner;
    GasStation gasStation;
    LinkedListQueue<Car> queue;

    CarStation station(&peopleDinner, &gasStation, &queue, &stats);

    station.serveCars();

    customAssert(stats.electricCarsCount() == 0, "Electric cars incorrectly counted when none were served.");
    customAssert(stats.gasCarsCount() == 0, "Gas cars incorrectly counted when none were served.");
    customAssert(stats.peopleServedCount() == 0, "People incorrectly served dinner when no cars present.");
    customAssert(stats.robotsServedCount() == 0, "Robots incorrectly served dinner when no cars present.");

    std::cout << "Test No Cars Passed!" << std::endl;
}

int main() {
    testFullService();
    testPartialService();
    testNoCars();
    return 0;
}
