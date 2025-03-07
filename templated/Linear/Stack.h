#include <exception>

#ifndef MY_DATA_STRUCTURES_STACK_H
#define MY_DATA_STRUCTURES_STACK_H

class StackEmptyException : public std::exception {
    public:
    const char *what() const noexcept override {
        return "Attempted to access top or pop from an empty stack";
    }
};


template <typename T>
class Stack {
    private:
    T *stack;
    size_t internalSize;  // Internal size of array used as Stack
    size_t elements;  // Number of elements in the Stack

    private:
    void _incrementSize(size_t);

    public:
    Stack();
    Stack(size_t);
    ~Stack();
    void push(T);
    void pop();
    T top();
    unsigned int size();
    bool empty();
    Stack &operator+=(const T &element);
};

#include "Stack.tpp"

#endif //MY_DATA_STRUCTURES_STACK_H
