#include <memory>
#include <random>
#include "ArrayQueue.h"
#include "CircularQueue.h"
#include "LinkedListQueue.h"

template <typename T>
std::shared_ptr<Queue<T>> createRandomQueue() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(0, 2);

    switch (dist(gen)) {
        case 0:
            return std::make_shared<ArrayQueue<T>>();
        case 1:
            return std::make_shared<CircularQueue<T>>(100);
        case 2:
            return std::make_shared<LinkedListQueue<T>>();
        default:
            throw std::logic_error("Invalid queue type");
    }
}
