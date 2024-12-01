#include "PeopleDinner.h"
#include "RobotDinner.h"
#include "ElectricStation.h"
#include "GasStation.h"
#include "utils/Statistics.h"

int main() {
    Statistics stats;

    PeopleDinner peopleDinner;
    RobotDinner robotDinner;
    ElectricStation electricStation;
    GasStation gasStation;

    peopleDinner.serveDinner("1");
    stats.incrementPeopleServed();

    robotDinner.serveDinner("2");
    stats.incrementRobotsServed();

    electricStation.refuel("3");
    stats.incrementElectricCars();

    gasStation.refuel("4");
    stats.incrementGasCars();

    stats.printStats();

    return 0;
}
