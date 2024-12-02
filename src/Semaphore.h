#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "CarStation.h"
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <dirent.h>
#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;

class Semaphore {
private:
    CarStation* electricCarStation;
    CarStation* gasCarStation;
    std::string folderPath;
    int readInterval;
    int serveInterval;

    std::mutex carQueueMutex;
    std::condition_variable carAvailable;
    bool carsInQueue = false;
    bool stopProcessing = false;

    void processFile(const std::string& filePath, const std::string& fileName) {
        std::ifstream inputFile(filePath);
        if (!inputFile.is_open()) {
            std::cerr << "[ERROR] Failed to open file: " << fileName << std::endl;
            return;
        }

        std::string jsonString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        json carJson = json::parse(jsonString);

        Car car(
            carJson["id"].get<int>(),
            carJson["type"].get<std::string>() == "ELECTRIC" ? CarType::ELECTRIC : CarType::GAS,
            carJson["passengers"].get<std::string>() == "PEOPLE" ? PassengerType::PEOPLE : PassengerType::ROBOTS,
            carJson["isDining"].get<bool>(),
            carJson["consumption"].get<int>()
        );

        if (car.getType() == CarType::ELECTRIC) {
            electricCarStation->addCar(car);
        } else {
            gasCarStation->addCar(car);
        }

        {
            std::lock_guard<std::mutex> lock(carQueueMutex);
            carsInQueue = true;
        }
        carAvailable.notify_one();

        std::cout << "[INFO] Processed file: " << fileName << " with content: " << jsonString << std::endl;
        std::remove(filePath.c_str());
    }

    void readTask() {
        DIR* dir = opendir(folderPath.c_str());
        if (!dir) {
            std::cerr << "[ERROR] Failed to open directory: " << folderPath << std::endl;
            stopProcessing = true; 
            carAvailable.notify_all();
            return;
        }

        struct dirent* entry;
        int totalFiles = 0;
        while ((entry = readdir(dir)) != nullptr) {
            std::string fileName = entry->d_name;

            if (fileName.size() > 5 && fileName.substr(fileName.size() - 5) == ".json") {
                std::string filePath = folderPath + "/" + fileName;
                processFile(filePath, fileName);
                totalFiles++;
                std::this_thread::sleep_for(std::chrono::seconds(readInterval));
            }
        }

        closedir(dir);

        if (totalFiles == 0) {
            std::cout << "[INFO] No files to process." << std::endl;
        }

        std::cout << "[INFO] Completed reading all files dynamically." << std::endl;
        stopProcessing = true;
        carAvailable.notify_all();
    }

    void serveTask() {
        while (true) {
            std::unique_lock<std::mutex> lock(carQueueMutex);

            carAvailable.wait(lock, [this] { 
                return carsInQueue || stopProcessing; 
            });

            if (stopProcessing && electricCarStation->getQueue()->isEmpty() && gasCarStation->getQueue()->isEmpty()) {
                std::cout << "[INFO] All cars served. Exiting serveTask." << std::endl;
                break;
            }

            if (!electricCarStation->getQueue()->isEmpty()) {
                electricCarStation->serveCar();
            } else if (!gasCarStation->getQueue()->isEmpty()) {
                gasCarStation->serveCar();
            }

            carsInQueue = !electricCarStation->getQueue()->isEmpty() || !gasCarStation->getQueue()->isEmpty();
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(serveInterval));
        }
    }

public:
    Semaphore(CarStation* electricStation, CarStation* gasStation, const std::string& folder, int readInt, int serveInt)
        : electricCarStation(electricStation), gasCarStation(gasStation), folderPath(folder), readInterval(readInt), serveInterval(serveInt) {}

    void start() {
        std::thread readerThread(&Semaphore::readTask, this);
        std::thread serveThread(&Semaphore::serveTask, this);

        readerThread.join();
        serveThread.join();
    }

    void printStatistics() const {
        const Statistics& electricStats = electricCarStation->getStatistics();
        const Statistics& gasStats = gasCarStation->getStatistics();

        std::cout << "{"
                  << "\"ELECTRIC\": " << electricStats.electricCarsCount() << ", "
                  << "\"GAS\": " << gasStats.gasCarsCount() << ", "
                  << "\"PEOPLE\": " << electricStats.peopleServedCount() + gasStats.peopleServedCount() << ", "
                  << "\"ROBOTS\": " << electricStats.robotsServedCount() + gasStats.robotsServedCount() << ", "
                  << "\"DINING\": " << electricStats.diningCarsCount() + gasStats.diningCarsCount() << ", "
                  << "\"NOT_DINING\": " << electricStats.notDiningCarsCount() + gasStats.notDiningCarsCount() << ", "
                  << "\"CONSUMPTION\": {"
                  << "\"ELECTRIC\": " << electricStats.electricConsumption() << ", "
                  << "\"GAS\": " << gasStats.gasConsumption()
                  << "}"
                  << "}" << std::endl;
    }
};

#endif
