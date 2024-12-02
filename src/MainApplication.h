#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include "Semaphore.h"
#include "CreateRandomQueue.cpp"
#include <string>

class MainApplication {
private:
    std::string folderPath;
    int readInterval;
    int serveInterval;

public:
    MainApplication(const std::string& folder, int readInt, int serveInt)
        : folderPath(folder), readInterval(readInt), serveInterval(serveInt) {}

    void start() {
        Semaphore semaphore(folderPath, readInterval, serveInterval);

        semaphore.addCarStation(std::make_shared<CarStation>(
            createRandomQueue<Car>(), CarType::ELECTRIC, PassengerType::PEOPLE));
        semaphore.addCarStation(std::make_shared<CarStation>(
            createRandomQueue<Car>(), CarType::ELECTRIC, PassengerType::ROBOTS));
        semaphore.addCarStation(std::make_shared<CarStation>(
            createRandomQueue<Car>(), CarType::GAS, PassengerType::PEOPLE));
        semaphore.addCarStation(std::make_shared<CarStation>(
            createRandomQueue<Car>(), CarType::GAS, PassengerType::ROBOTS));

        semaphore.start();
    }
};

#endif
