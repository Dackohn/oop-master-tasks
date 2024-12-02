#ifndef CAR_STATION_H
#define CAR_STATION_H

#include "interfaces/Dineable.h"
#include "interfaces/Refuelable.h"
#include "utils/Statistics.h"
#include "interfaces/Queue.h"
#include "Car.h"
#include <iostream>

class CarStation {
private:
    Dineable* diningService;
    Refuelable* refuelingService;
    Queue<Car>* queue;
    Statistics* stats;

public:
    CarStation(Dineable* dineService, Refuelable* refuelService, Queue<Car>* carQueue, Statistics* statistics)
        : diningService(dineService), refuelingService(refuelService), queue(carQueue), stats(statistics) {}

    void addCar(const Car& car) {
        queue->enqueue(car);
    }

    void serveCars() {
    while (!queue->isEmpty()) {
        Car car = queue->dequeue();

        if (car.needsDinner()) {
            if (car.getPassengers() == PassengerType::PEOPLE) {
                diningService->serveDinner(car.getId());
                stats->incrementPeopleServed();
            } else if (car.getPassengers() == PassengerType::ROBOTS) {
                diningService->serveDinner(car.getId());
                stats->incrementRobotsServed();
            }
        }

        if (car.getType() == CarType::ELECTRIC) {
            refuelingService->refuel(car.getId());
            stats->incrementElectricCars();
        } else if (car.getType() == CarType::GAS) {
            refuelingService->refuel(car.getId());
            stats->incrementGasCars();
        }
    }
}

};

#endif
