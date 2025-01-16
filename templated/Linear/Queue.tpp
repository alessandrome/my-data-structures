#include <exception>
#include "Queue.h"

#ifndef DEFAULT_QUEUE_SIZE
#define DEFAULT_QUEUE_SIZE 10
#endif

#ifndef DEFAULT_QUEUE_SIZE_INCREMENT
#define DEFAULT_QUEUE_SIZE_INCREMENT 10
#endif


// (De)Constructor
template <typename T>
Queue<T>::Queue(): internalSize(DEFAULT_QUEUE_SIZE), elements(0) {
    arr = new T[DEFAULT_QUEUE_SIZE];
}
template <typename T>
Queue<T>::Queue(size_t startingSize): internalSize(startingSize), elements(0) {
    arr = new T[startingSize];
}
template <typename T>
Queue<T>::~Queue() {
    delete[] arr;  // Deallocate dynamic pointed array
}


// Public methods
template <typename T>
void Queue<T>::push(T element) {
    if (internalSize == elements) {
        // Resize
        _incrementSize(DEFAULT_QUEUE_SIZE_INCREMENT);
    }
    arr[elements++] = element;
}

template <typename T>
T Queue<T>::pop() {
    if (elements > 0) {
        T to_return = arr[0];
        elements--;
        // Move all elements to gain one position
        for (int i=0; i < elements; i++) {
            arr[i] = arr[i + 1];
        }
        return to_return;
    }
    throw QueueEmptyException();
}

template <typename T>
T Queue<T>::front() {
    if (elements > 0) return arr[0];
    else throw QueueEmptyException();
}

template <typename T>
T Queue<T>::back() {
    if (elements > 0) return arr[elements - 1];
    throw QueueEmptyException();
}

template <typename T>
unsigned int Queue<T>::size() {
    return elements;
}

template <typename T>
bool Queue<T>::empty() {
    return elements <= 0;
}


// Private methods
template <typename T>
void Queue<T>::_incrementSize(int increment) {
    T* oldArr = arr;
    arr = new T[internalSize + increment];  // TODO: We're not checking if new allocation is done successfully (no NULL pointer)
    for (int i=0; i < elements; i++) {
        arr[i] = oldArr[i];
    }
    delete[] oldArr;
}

// Operator Overloads
template <typename T>
Queue<T> &Queue<T>::operator+=(const T &val) {
    push(val);
    return *this;
}
