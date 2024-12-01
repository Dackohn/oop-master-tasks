#include "interfaces/Queue.h"
#include <memory>

template <typename T>
class LinkedListQueue : public Queue<T> {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        Node(const T& d) : data(d), next(nullptr) {}
    };

    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    size_t count;

public:
    LinkedListQueue() : head(nullptr), tail(nullptr), count(0) {}

    void enqueue(const T& item) override {
        auto newNode = std::make_shared<Node>(item);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    T dequeue() override {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        T item = head->data;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
        count--;
        return item;
    }

    T peek() const override {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return head->data;
    }

    bool isEmpty() const override {
        return count == 0;
    }

    size_t size() const override {
        return count;
    }
};
