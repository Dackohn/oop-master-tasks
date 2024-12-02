#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iostream>

template <typename T>
class Queue {
public:
    virtual void enqueue(const T& item) = 0;
    virtual T dequeue() = 0;       
    virtual T peek() const = 0;     
    virtual bool isEmpty() const = 0;       
    virtual size_t size() const = 0;      
    virtual ~Queue() = default;
};

#endif
