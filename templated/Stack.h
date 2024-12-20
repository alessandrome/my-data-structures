#include <exception>

#ifndef MY_DATA_STRUCTURES_STACK_H
#define MY_DATA_STRUCTURES_STACK_H

class StackEmptyException : public std::exception {
    public:
    const char* what() const noexcept override {
        return "Attempted to access top or pop from an empty stack";
    }
};


template <typename T>
class Stack {
    private:
    T* stack;
    unsigned int internalSize;  // Internal size of array used as Stack
    unsigned int elements;  // Number of elements in the Stack

    public:
    Stack();
    ~Stack();
    void push(T);
    void pop();
    T top();
    unsigned int size();
    bool empty();

    private:
    void _incrementSize(int);
};

#include "Stack.tpp"

#endif //MY_DATA_STRUCTURES_STACK_H
