#ifndef CAR_H
#define CAR_H

#include <string>

enum class CarType { ELECTRIC, GAS };
enum class PassengerType { PEOPLE, ROBOTS };

class Car {
private:
    int id;
    CarType type;
    PassengerType passengers;
    bool wantsDinner;
    int consumption;

public:
    Car()
        : id(0), type(CarType::ELECTRIC), passengers(PassengerType::PEOPLE), wantsDinner(false), consumption(0) {}

    Car(const int& carId, CarType carType, PassengerType passengerType, bool dinnerPreference, int consumptionValue)
        : id(carId), type(carType), passengers(passengerType), wantsDinner(dinnerPreference), consumption(consumptionValue) {}

    int getId() const { return id; }
    CarType getType() const { return type; }
    PassengerType getPassengers() const { return passengers; }
    bool needsDinner() const { return wantsDinner; }
    int getConsumption() const { return consumption; }
};

#endif
