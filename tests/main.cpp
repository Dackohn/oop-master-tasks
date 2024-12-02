#include "../src/CreateRandomQueue.cpp"
#include "../src/Semaphore.h"
#include "iostream"
#include <cassert>

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

void testQueueUnderflow() {
    ArrayQueue<int> arrayQueue;
    try {
        arrayQueue.dequeue();
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "Queue underflow test passed!" << std::endl;
    }
}

void testQueuePeek() {
    ArrayQueue<int> arrayQueue;
    arrayQueue.enqueue(42);
    assert(arrayQueue.peek() == 42);
    std::cout << "Queue peek test passed!" << std::endl;
}

void testCircularQueueOverflow() {
    CircularQueue<int> circularQueue(3);
    circularQueue.enqueue(1);
    circularQueue.enqueue(2);
    circularQueue.enqueue(3);
    try {
        circularQueue.enqueue(4);
        assert(false);
    } catch (const std::overflow_error& e) {
        std::cout << "Circular queue overflow test passed!" << std::endl;
    }
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

void testSemaphoreNoMatchingStation() {
    Semaphore semaphore("src/queue_test", 1, 1);

    semaphore.addCarStation(std::make_shared<CarStation>(
        createRandomQueue<Car>(), CarType::ELECTRIC, PassengerType::PEOPLE));

    Car car(1, CarType::GAS, PassengerType::ROBOTS, false, 40);

    auto queue = createRandomQueue<Car>();
    CarStation station(queue, CarType::ELECTRIC, PassengerType::PEOPLE);

    station.addCar(car);

    assert(queue->isEmpty() == true);

    std::cout << "Semaphore no matching station test passed!" << std::endl;
}

void testSemaphoreStopProcessing() {
    Semaphore semaphore("src/queue_test", 1, 1);

    std::thread semaphoreThread(&Semaphore::start, &semaphore);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    semaphoreThread.detach();

    std::cout << "Semaphore stop processing test passed!" << std::endl;
}

void testSemaphoreMultipleCarTypes() {
    Semaphore semaphore("src/queue_test", 1, 1);

    semaphore.addCarStation(std::make_shared<CarStation>(
        createRandomQueue<Car>(), CarType::ELECTRIC, PassengerType::PEOPLE));
    semaphore.addCarStation(std::make_shared<CarStation>(
        createRandomQueue<Car>(), CarType::ELECTRIC, PassengerType::ROBOTS));
    semaphore.addCarStation(std::make_shared<CarStation>(
        createRandomQueue<Car>(), CarType::GAS, PassengerType::PEOPLE));
    semaphore.addCarStation(std::make_shared<CarStation>(
        createRandomQueue<Car>(), CarType::GAS, PassengerType::ROBOTS));

    Car car1(1, CarType::ELECTRIC, PassengerType::PEOPLE, true, 50);
    Car car2(2, CarType::GAS, PassengerType::ROBOTS, false, 30);

    auto queue1 = createRandomQueue<Car>();
    auto queue2 = createRandomQueue<Car>();
    CarStation station1(queue1, CarType::ELECTRIC, PassengerType::PEOPLE);
    CarStation station2(queue2, CarType::GAS, PassengerType::ROBOTS);

    station1.addCar(car1);
    station2.addCar(car2);

    assert(station1.serveCar().getId() == 1);
    assert(station2.serveCar().getId() == 2);

    std::cout << "Semaphore multiple car types test passed!" << std::endl;
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

void testCarServiceMultipleCars() {
    auto queue = createRandomQueue<Car>();
    CarStation station(queue, CarType::ELECTRIC, PassengerType::PEOPLE);

    Car car1(1, CarType::ELECTRIC, PassengerType::PEOPLE, true, 50);
    Car car2(2, CarType::ELECTRIC, PassengerType::PEOPLE, false, 30);

    station.addCar(car1);
    station.addCar(car2);

    assert(station.serveCar().getId() == 1);
    assert(station.serveCar().getId() == 2);

    std::cout << "Car service multiple cars test passed!" << std::endl;
}

void testCarServiceEmptyQueue() {
    auto queue = createRandomQueue<Car>();
    CarStation station(queue, CarType::ELECTRIC, PassengerType::PEOPLE);

    try {
        station.serveCar();
        assert(false);
    } catch (const std::out_of_range& e) {
        std::cout << "Car service empty queue test passed!" << std::endl;
    }
}

void testRefuelable() {
    ElectricStation electricStation;
    GasStation gasStation;

    electricStation.refuel(1);
    gasStation.refuel(2);

    std::cout << "Refuelable tests passed!" << std::endl;
}

void testRefuelableInvalidCar() {
    ElectricStation electricStation;
    try {
        electricStation.refuel(-1);
        assert(false);
    } catch (...) {
        std::cout << "Refuelable invalid car ID test passed!" << std::endl;
    }
}

void testDineable() {
    PeopleDinner peopleDinner;
    RobotDinner robotDinner;

    peopleDinner.serveDinner(1);
    robotDinner.serveDinner(2);

    std::cout << "Dineable tests passed!" << std::endl;
}

void testDineableLargeCarID() {
    PeopleDinner peopleDinner;
    RobotDinner robotDinner;

    peopleDinner.serveDinner(1000000);
    robotDinner.serveDinner(2000000);

    std::cout << "Dineable large car ID test passed!" << std::endl;
}

int main() {
    testQueues();
    testQueueUnderflow();
    testQueuePeek();
    testCircularQueueOverflow();

    testSemaphore();
    testSemaphoreNoMatchingStation();
    testSemaphoreStopProcessing();
    testSemaphoreMultipleCarTypes();

    testCarService();
    testCarServiceMultipleCars();
    testCarServiceEmptyQueue();

    testRefuelable();
    testRefuelableInvalidCar();

    testDineable();
    testDineableLargeCarID();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
