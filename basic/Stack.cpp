#include <exception>
#include "Stack.h"

#ifndef DEFAULT_STACK_SIZE
#define DEFAULT_STACK_SIZE 10
#endif

#ifndef DEFAULT_STACK_SIZE_INCREMENT
#define DEFAULT_STACK_SIZE_INCREMENT 10
#endif


// (De)Constructor
Stack::Stack(): internalSize(0), elements(0) {
    stack = new int[DEFAULT_STACK_SIZE];
    internalSize = DEFAULT_STACK_SIZE;
}
Stack::~Stack() {
    delete[] stack;  // Dealloca la memoria per l'array dinamico
}


// Public methods
void Stack::push(int element) {
    if (internalSize == elements) {
        // Resize
        _incrementSize(DEFAULT_STACK_SIZE_INCREMENT);
    }
    stack[elements++] = element;
}

void Stack::pop() {
    if (elements > 0) elements--;
    else throw StackEmptyException();
}

int Stack::top() {
    if (elements > 0) return stack[elements - 1];
    throw StackEmptyException();
}

unsigned int Stack::size() {
    return elements;
}

bool Stack::empty() {
    return elements <= 0;
}


// Private methods
void Stack::_incrementSize(int increment) {
    int* oldStack = stack;
    stack = new int[internalSize + increment];  // TODO: We're not checking if new allocation is done successfully (no NULL pointer)
    for (int i=0; i < elements; i++) {
        stack[i] = oldStack[i];
    }
    delete[] oldStack;
}
