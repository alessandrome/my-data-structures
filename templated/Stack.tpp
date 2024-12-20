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
Stack<T>::Stack(): internalSize(0), elements(0) {
    stack = new T[DEFAULT_STACK_SIZE];
    internalSize = DEFAULT_STACK_SIZE;
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


// Private methods
template <typename T>
void Stack<T>::_incrementSize(int increment) {
    T* oldStack = stack;
    stack = new T[internalSize + increment];  // TODO: We're not checking if new allocation is done successfully (no NULL pointer)
    for (int i=0; i < elements; i++) {
        stack[i] = oldStack[i];
    }
    delete[] oldStack;
}
