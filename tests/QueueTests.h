#include "../src/ArrayQueue.h"
#include "../src/LinkedListQueue.h"
#include "../src/CircularQueue.h"
#include <cassert>
#include <iostream>
#include <string>

void testIntegerQueue(Queue<int>& queue) {
    assert(queue.isEmpty());
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    assert(queue.size() == 3);
    assert(queue.peek() == 1);
    assert(queue.dequeue() == 1);
    assert(queue.size() == 2);
    std::cout << "Integer Queue tests passed!" << std::endl;
}

void testStringQueue(Queue<std::string>& queue) {
    assert(queue.isEmpty());
    queue.enqueue("Car1");
    queue.enqueue("Car2");
    queue.enqueue("Car3");
    assert(queue.size() == 3);
    assert(queue.peek() == "Car1");
    assert(queue.dequeue() == "Car1");
    assert(queue.size() == 2);
    std::cout << "String Queue tests passed!" << std::endl;
}
