#include <exception>

#ifndef MY_DATA_STRUCTURES_QUEUE_H
#define MY_DATA_STRUCTURES_QUEUE_H

class QueueEmptyException : public std::exception {
    public:
    const char* what() const noexcept override {
        return "Attempted to access top or pop from an empty stack";
    }
};


template <typename T>
class Queue {
    private:
    T* arr;  // Pointer to dynamic array where push elements
    unsigned int internalSize;  // Internal size of array used as Queue
    unsigned int elements;  // Number of elements in the Queue
    public:
    Queue();
    ~Queue();
    void push(T);
    T pop();
    T front();
    T back();
    unsigned int size();
    bool empty();

    private:
    void _incrementSize(int);
};

#include "Queue.tpp"

#endif //MY_DATA_STRUCTURES_QUEUE_H
