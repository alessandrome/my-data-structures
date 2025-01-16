#include <exception>
#include "Stack.h"

#ifndef DEFAULT_STACK_SIZE
#define DEFAULT_STACK_SIZE 10
#endif

#ifndef DEFAULT_STACK_SIZE_INCREMENT
#define DEFAULT_STACK_SIZE_INCREMENT 10
#endif


// (De)Constructor
template <typename T>
Stack<T>::Stack(): internalSize(DEFAULT_STACK_SIZE), elements(0) {
    stack = new T[DEFAULT_STACK_SIZE];
}
template <typename T>
Stack<T>::Stack(size_t startingCapacity): internalSize(startingCapacity), elements(0) {
    stack = new T[startingCapacity];
}
template <typename T>
Stack<T>::~Stack() {
    delete[] stack;  // Dealloca la memoria per l'array dinamico
}


// Public methods
template <typename T>
void Stack<T>::push(T element) {
    if (internalSize == elements) {
        // Resize
        _incrementSize(DEFAULT_STACK_SIZE_INCREMENT);
    }
    stack[elements++] = element;
}

template <typename T>
void Stack<T>::pop() {
    if (elements > 0) elements--;
    else throw StackEmptyException();
}

template <typename T>
T Stack<T>::top() {
    if (elements > 0) return stack[elements - 1];
    throw StackEmptyException();
}

template <typename T>
unsigned int Stack<T>::size() {
    return elements;
}

template <typename T>
bool Stack<T>::empty() {
    return elements <= 0;
}

template <typename T>
Stack<T>& Stack<T>::operator+=(const T& element) {
    push(element);
    return *this;
}


// Private methods
template <typename T>
void Stack<T>::_incrementSize(size_t increment) {
    T* oldStack = stack;
    stack = new T[internalSize + increment];  // TODO: We're not checking if new allocation is done successfully (no NULL pointer)
    // We're going to copy the old array in the new one
    for (size_t i=0; i < elements; i++) {
        stack[i] = oldStack[i];
    }
    delete[] oldStack;
}
