#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "CarStation.h"
#include "ElectricStation.h"
#include "GasStation.h"
#include "PeopleDinner.h"
#include "RobotDinner.h"
#include "utils/Statistics.h"
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
    std::vector<std::shared_ptr<CarStation>> carStations;
    std::string folderPath;
    int readInterval;
    int serveInterval;

    std::mutex carQueueMutex;
    std::condition_variable carAvailable;
    bool carsInQueue = false;
    bool stopProcessing = false;

    Statistics stats;

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

        for (const auto& station : carStations) {
            if (station->getStationType() == car.getType() &&
                station->getDiningType() == car.getPassengers()) {
                station->addCar(car);

                if (car.getType() == CarType::ELECTRIC) {
                    stats.incrementElectricCars();
                } else if (car.getType() == CarType::GAS) {
                    stats.incrementGasCars();
                }

                if (car.getPassengers() == PassengerType::PEOPLE) {
                    stats.incrementPeopleServed();
                } else if (car.getPassengers() == PassengerType::ROBOTS) {
                    stats.incrementRobotsServed();
                }

                if (car.needsDinner()) {
                    stats.incrementDiningCars();
                } else {
                    stats.incrementNotDiningCars();
                }

                break;
            }
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
        while ((entry = readdir(dir)) != nullptr) {
            std::string fileName = entry->d_name;

            if (fileName.size() > 5 && fileName.substr(fileName.size() - 5) == ".json") {
                std::string filePath = folderPath + "/" + fileName;
                processFile(filePath, fileName);
                std::this_thread::sleep_for(std::chrono::seconds(readInterval));
            }
        }

        closedir(dir);
        stopProcessing = true;
        carAvailable.notify_all();
    }

    void serveTask() {
        while (true) {
            std::unique_lock<std::mutex> lock(carQueueMutex);

            carAvailable.wait(lock, [this] { return carsInQueue || stopProcessing; });

            if (stopProcessing && !hasCarsInQueue()) {
                break;
            }

            for (const auto& station : carStations) {
                if (!station->getQueue()->isEmpty()) {
                    Car servedCar = station->serveCar();

                    if (servedCar.getId() != -1) {

                        if (servedCar.getType() == CarType::ELECTRIC) {
                            ElectricStation().refuel(servedCar.getId());
                            stats.addElectricConsumption(servedCar.getConsumption());
                        } else if (servedCar.getType() == CarType::GAS) {
                            GasStation().refuel(servedCar.getId());
                            stats.addGasConsumption(servedCar.getConsumption());
                        }

                        if (servedCar.needsDinner()) {
                            if (servedCar.getPassengers() == PassengerType::PEOPLE) {
                                PeopleDinner().serveDinner(servedCar.getId());
                            } else {
                                RobotDinner().serveDinner(servedCar.getId());
                            }
                        }
                    }
                }
            }

            carsInQueue = hasCarsInQueue();
            lock.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(serveInterval));
        }
    }

    bool hasCarsInQueue() const {
        for (const auto& station : carStations) {
            if (!station->getQueue()->isEmpty()) {
                return true;
            }
        }
        return false;
    }

public:
    Semaphore(const std::string& folder, int readInt, int serveInt)
        : folderPath(folder), readInterval(readInt), serveInterval(serveInt) {}

    void addCarStation(std::shared_ptr<CarStation> station) {
        carStations.push_back(station);
    }

    void start() {
        std::thread readerThread(&Semaphore::readTask, this);
        std::thread serveThread(&Semaphore::serveTask, this);

        readerThread.join();
        serveThread.join();
        printStatistics();
    }

    void printStatistics() const {
        stats.printStats();
    }
};

#endif
