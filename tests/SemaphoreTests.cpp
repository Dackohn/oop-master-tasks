#include "../src/Semaphore.h"
#include "../src/LinkedListQueue.h"
#include "../src/PeopleDinner.h"
#include "../src/RobotDinner.h"
#include "../src/ElectricStation.h"
#include "../src/GasStation.h"
#include "../src/utils/Statistics.h"

void customAssert(bool condition, const std::string& errorMessage) {
    if (!condition) {
        std::cerr << "Test failed: " << errorMessage << std::endl;
        exit(EXIT_FAILURE);
    }
}

void testSemaphore() {
    Statistics electricStats, gasStats;

    PeopleDinner electricPeopleDinner;
    RobotDinner gasRobotDinner;
    ElectricStation electricRefuel;
    GasStation gasRefuel;

    LinkedListQueue<Car> electricQueue, gasQueue;

    CarStation electricStation(&electricPeopleDinner, &electricRefuel, &electricQueue, &electricStats);
    CarStation gasStation(&gasRobotDinner, &gasRefuel, &gasQueue, &gasStats);

    Semaphore semaphore(&electricStation, &gasStation);

    std::vector<std::string> carJsonStrings = {
        R"({"id": "1", "type": "ELECTRIC", "passengers": "PEOPLE", "isDining": true})",
        R"({"id": "2", "type": "GAS", "passengers": "ROBOTS", "isDining": true})",
        R"({"id": "3", "type": "ELECTRIC", "passengers": "PEOPLE", "isDining": false})",
        R"({"id": "4", "type": "GAS", "passengers": "ROBOTS", "isDining": false})"
    };

    for (const auto& jsonString : carJsonStrings) {
        semaphore.processJson(jsonString);
    }

    semaphore.serveCars();

    customAssert(electricStats.electricCarsCount() == 2, "Incorrect number of electric cars served.");
    customAssert(electricStats.peopleServedCount() == 1, "Incorrect number of people served dinner for electric cars.");
    customAssert(gasStats.gasCarsCount() == 2, "Incorrect number of gas cars served.");
    customAssert(gasStats.robotsServedCount() == 1, "Incorrect number of robots served dinner for gas cars.");

    std::cout << "Test Semaphore Passed!" << std::endl;
}

int main() {
    testSemaphore();
    return 0;
}
