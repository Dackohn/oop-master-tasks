#include "interfaces/Queue.h"
#include <vector>

template <typename T>
class ArrayQueue : public Queue<T> {
private:
    std::vector<T> data;

public:
    void enqueue(const T& item) override {
        data.push_back(item);
    }

    T dequeue() override {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        T item = data.front();
        data.erase(data.begin());
        return item;
    }

    T peek() const override {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data.front();
    }

    bool isEmpty() const override {
        return data.empty();
    }

    size_t size() const override {
        return data.size();
    }
};
