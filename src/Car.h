#ifndef CAR_H
#define CAR_H

#include <string>

enum class CarType { ELECTRIC, GAS };
enum class PassengerType { PEOPLE, ROBOTS };

class Car {
private:
    std::string id;
    CarType type;
    PassengerType passengers;
    bool wantsDinner;

public:
    Car(const std::string& carId, CarType carType, PassengerType passengerType, bool dinnerPreference)
        : id(carId), type(carType), passengers(passengerType), wantsDinner(dinnerPreference) {}

    std::string getId() const { return id; }
    CarType getType() const { return type; }
    PassengerType getPassengers() const { return passengers; }
    bool needsDinner() const { return wantsDinner; }
};

#endif
