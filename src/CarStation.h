#ifndef CARSTATION_H
#define CARSTATION_H

#include "CircularQueue.h"
#include "Car.h"
#include "utils/Statistics.h"
#include <iostream>

class CarStation {
private:
    CircularQueue<Car>* carQueue;
    Statistics* stats;

public:
    CarStation(CircularQueue<Car>* queue, Statistics* statistics)
        : carQueue(queue), stats(statistics) {}

    void addCar(const Car& car) {
        carQueue->enqueue(car);
        std::cout << "[INFO] Added car ID: " << car.getId()
                  << " to " << (car.getType() == CarType::ELECTRIC ? "electric" : "gas") << " queue." << std::endl;
    }

    void serveCar() {
        if (carQueue->isEmpty()) {
            std::cout << "[INFO] No cars to serve in this station." << std::endl;
            return;
        }

        Car car = carQueue->dequeue();

        if (car.getType() == CarType::ELECTRIC) {
            stats->incrementElectricCars();
            stats->addElectricConsumption(car.getConsumption());
        } else {
            stats->incrementGasCars();
            stats->addGasConsumption(car.getConsumption());
        }

        if (car.getPassengers() == PassengerType::PEOPLE) {
            stats->incrementPeopleServed();
        } else {
            stats->incrementRobotsServed();
        }

        if (car.needsDinner()) {
            stats->incrementDiningCars();
        } else {
            stats->incrementNotDiningCars();
        }

        std::cout << "[INFO] Served car ID: " << car.getId()
                  << " from " << (car.getType() == CarType::ELECTRIC ? "electric" : "gas") << " queue."
                  << " Passengers: " << (car.getPassengers() == PassengerType::PEOPLE ? "People" : "Robots")
                  << (car.needsDinner() ? " with dinner." : " without dinner.") << std::endl;
    }

    CircularQueue<Car>* getQueue() const {
        return carQueue;
    }

    Statistics& getStatistics() const {
        return *stats;
    }
};

#endif
