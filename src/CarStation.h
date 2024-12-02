#ifndef CARSTATION_H
#define CARSTATION_H

#include "Car.h"
#include "interfaces/Queue.h"
#include <memory>
#include <iostream>
#include <string>

class CarStation {
private:
    std::shared_ptr<Queue<Car>> carQueue;
    CarType stationType;
    PassengerType diningType;

public:
    CarStation(std::shared_ptr<Queue<Car>> queue, CarType type, PassengerType dinerType)
        : carQueue(queue), stationType(type), diningType(dinerType) {}

    void addCar(const Car& car) {
        if (car.getType() != stationType) {
            std::cerr << "[ERROR] Car ID: " << car.getId()
                      << " is incompatible with this station's type (" 
                      << (stationType == CarType::ELECTRIC ? "ELECTRIC" : "GAS") << ")." << std::endl;
            return;
        }
        carQueue->enqueue(car);
        std::cout << "[INFO] Added car ID: " << car.getId()
                  << " to " << (stationType == CarType::ELECTRIC ? "electric" : "gas") << " queue." << std::endl;
    }

    Car serveCar() {
        if (carQueue->isEmpty()) {
            std::cerr << "[INFO] No cars to serve in this station." << std::endl;
            return Car(-1, stationType, diningType, false, 0); // Return a dummy car
        }

        Car car = carQueue->dequeue();

        if (car.getPassengers() != diningType) {
            std::cerr << "[ERROR] Car ID: " << car.getId()
                      << " passengers are incompatible with this station's dining setup ("
                      << (diningType == PassengerType::PEOPLE ? "PEOPLE" : "ROBOTS") << ")." << std::endl;
            return Car(-1, stationType, diningType, false, 0); // Return a dummy car
        }

        std::cout << "[INFO] Served car ID: " << car.getId()
                  << " from " << (stationType == CarType::ELECTRIC ? "electric" : "gas") << " queue."
                  << " Passengers: " << (car.getPassengers() == PassengerType::PEOPLE ? "People" : "Robots")
                  << (car.needsDinner() ? " with dinner." : " without dinner.") << std::endl;

        return car;
    }

    std::shared_ptr<Queue<Car>> getQueue() const {
        return carQueue;
    }

    CarType getStationType() const {
        return stationType;
    }

    PassengerType getDiningType() const {
        return diningType;
    }
};

#endif
