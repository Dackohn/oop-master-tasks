#include "QueueTests.h"
#include "DineableTests.h"
#include "RefuebleTests.h"
#include <cassert>
#include <iostream>
#include <string>


int main() {
    ArrayQueue<int> intArrayQueue;
    testIntegerQueue(intArrayQueue);

    LinkedListQueue<std::string> stringLinkedListQueue;
    testStringQueue(stringLinkedListQueue);

    CircularQueue<int> intCircularQueue(5);
    testIntegerQueue(intCircularQueue);

    return 0;
}