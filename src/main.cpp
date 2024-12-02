#include "Semaphore.h"
#include "LinkedListQueue.h"
#include "PeopleDinner.h"
#include "RobotDinner.h"
#include "ElectricStation.h"
#include "GasStation.h"
#include "utils/Statistics.h"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void testSemaphore(const std::string& folderPath) {
    Statistics electricStats, gasStats;
    PeopleDinner peopleDinner;
    RobotDinner robotDinner;
    ElectricStation electricRefuel;
    GasStation gasRefuel;

    LinkedListQueue<Car> electricQueue, gasQueue;
    CarStation electricStation(&peopleDinner, &electricRefuel, &electricQueue, &electricStats);
    CarStation gasStation(&robotDinner, &gasRefuel, &gasQueue, &gasStats);

    Semaphore semaphore(&electricStation, &gasStation);

    DIR* dir = opendir(folderPath.c_str());
    if (!dir) {
        std::cerr << "Failed to open directory: " << folderPath << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string fileName = entry->d_name;

        if (fileName.size() > 5 && fileName.substr(fileName.size() - 5) == ".json") {
            std::ifstream inputFile(folderPath + "/" + fileName);
            if (!inputFile.is_open()) {
                std::cerr << "Failed to open file: " << fileName << std::endl;
                continue;
            }

            std::string jsonString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
            semaphore.processJson(jsonString);
        }
    }

    closedir(dir);

    semaphore.serveCars();


    std::cout << "Test Passed!" << std::endl;
}

int main() {
    std::string folderPath = "queue";
    testSemaphore(folderPath);
    return 0;
}
