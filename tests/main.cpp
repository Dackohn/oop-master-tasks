
#include "../src/CreateRandomQueue.cpp"
#include "../src/Semaphore.h"
#include "iostream"
void testQueues() {
    ArrayQueue<int> arrayQueue;
    CircularQueue<int> circularQueue(10);
    LinkedListQueue<int> linkedListQueue;

    arrayQueue.enqueue(1);
    circularQueue.enqueue(2);
    linkedListQueue.enqueue(3);

    assert(arrayQueue.dequeue() == 1);
    assert(circularQueue.dequeue() == 2);
    assert(linkedListQueue.dequeue() == 3);

    std::cout << "All queue tests passed!" << std::endl;
}
void testSemaphore() {
    Semaphore semaphore("src/queue_test", 1, 1);

    semaphore.addCarStation(std::make_shared<CarStation>(
        createRandomQueue<Car>(), CarType::ELECTRIC, PassengerType::PEOPLE));
    semaphore.addCarStation(std::make_shared<CarStation>(
        createRandomQueue<Car>(), CarType::GAS, PassengerType::ROBOTS));

    std::thread semaphoreThread(&Semaphore::start, &semaphore);
    semaphoreThread.join();

    std::cout << "Semaphore test passed!" << std::endl;
}

void testCarService() {
    Car car1(1, CarType::ELECTRIC, PassengerType::PEOPLE, true, 50);
    Car car2(2, CarType::GAS, PassengerType::ROBOTS, false, 40);

    auto queue = createRandomQueue<Car>();
    CarStation station(queue, CarType::ELECTRIC, PassengerType::PEOPLE);

    station.addCar(car1);
    assert(station.serveCar().getId() == 1);

    std::cout << "Car service tests passed!" << std::endl;
}

void testRefuelable() {
    ElectricStation electricStation;
    GasStation gasStation;

    electricStation.refuel(1);
    gasStation.refuel(2);

    std::cout << "Refuelable tests passed!" << std::endl;
}

void testDineable() {
    PeopleDinner peopleDinner;
    RobotDinner robotDinner;

    peopleDinner.serveDinner(1);
    robotDinner.serveDinner(2);

    std::cout << "Dineable tests passed!" << std::endl;
}
int main() {
    testQueues();
    testSemaphore();
    testCarService();
    testRefuelable();
    testDineable();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
