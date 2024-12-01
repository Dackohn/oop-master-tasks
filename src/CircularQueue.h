#include "interfaces/Queue.h"
#include <vector>

template <typename T>
class CircularQueue : public Queue<T> {
private:
    std::vector<T> data;
    size_t head, tail, capacity;
    size_t count;

public:
    explicit CircularQueue(size_t cap) : data(cap), head(0), tail(0), capacity(cap), count(0) {}

    void enqueue(const T& item) override {
        if (count == capacity) {
            throw std::overflow_error("Queue is full");
        }
        data[tail] = item;
        tail = (tail + 1) % capacity;
        count++;
    }

    T dequeue() override {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        T item = data[head];
        head = (head + 1) % capacity;
        count--;
        return item;
    }

    T peek() const override {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data[head];
    }

    bool isEmpty() const override {
        return count == 0;
    }

    size_t size() const override {
        return count;
    }
};
