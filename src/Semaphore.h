#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "CarStation.h"
#include "../include/nlohmann/json.hpp"
#include <vector>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

class Semaphore {
private:
    CarStation* electricCarStation;
    CarStation* gasCarStation;

public:
    Semaphore(CarStation* electricStation, CarStation* gasStation)
        : electricCarStation(electricStation), gasCarStation(gasStation) {}

    void processJson(const std::string& jsonString) {
        json carJson;
        try {
            carJson = json::parse(jsonString);
        } catch (const json::parse_error& e) {
            std::cerr << "JSON Parse Error: " << e.what() << std::endl;
            return;
        }

        int id = carJson["id"].get<int>(); // Retrieve `id` as an integer

        Car car(
            std::to_string(id), // Convert `id` to string only for compatibility with the Car constructor
            carJson["type"].get<std::string>() == "ELECTRIC" ? CarType::ELECTRIC : CarType::GAS,
            carJson["passengers"].get<std::string>() == "PEOPLE" ? PassengerType::PEOPLE : PassengerType::ROBOTS,
            carJson["isDining"].get<bool>()
        );

        if (car.getType() == CarType::ELECTRIC) {
            electricCarStation->addCar(car);
        } else {
            gasCarStation->addCar(car);
        }
    }

    void serveCars() {
        electricCarStation->serveCars();
        gasCarStation->serveCars();
    }
};

#endif
