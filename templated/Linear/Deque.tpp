#include "Deque.h"

namespace myds {
    template <typename T>
    myds::Deque<T>::Deque(): _length(0), _capacity(DEFAULT_DEQUE_CAPACITY), _headIndex(0), _tailIndex(0) {
        _array = new T[DEFAULT_DEQUE_CAPACITY];
    }
    template <typename T>
    myds::Deque<T>::Deque(size_t startingCapacity): _length(0), _capacity(startingCapacity), _headIndex(0), _tailIndex(0) {
        _array = new T[startingCapacity];
    }
    template <typename T>
    myds::Deque<T>::~Deque() {
        delete[] _array;
    }

    template <typename T>
    size_t myds::Deque<T>::length() const { return _length; }
    template <typename T>
    bool myds::Deque<T>::empty() const { return _length == 0; }


    template <typename T>
    void myds::Deque<T>::pushFront(const T &value) {
        if (_length == _capacity) {
            _increaseCapacity(DEFAULT_DEQUE_CAPACITY_INCREMENT);
        }
        _headIndex = _headIndex == 0 ? _capacity - 1 : _headIndex - 1;
        _array[_headIndex] = value;
        _length++;
    }
    template <typename T>
    void myds::Deque<T>::pushBack(const T &value) {
        if (_length == _capacity) {
            _increaseCapacity(DEFAULT_DEQUE_CAPACITY_INCREMENT);
        }
        _tailIndex = (_tailIndex + 1) % _capacity;
        _array[_tailIndex] = value;
        _length++;
    }

    template <typename T>
    T myds::Deque<T>::popFront() {
        T &toReturn = _array[_headIndex++];
        _headIndex %= _capacity;
        _length--;
        return toReturn;
    }
    template <typename T>
    T myds::Deque<T>::popBack() {
        T &toReturn = _array[_tailIndex];
        _tailIndex = _tailIndex == 0 ? _capacity - 1 : _tailIndex - 1;
        _length--;
        return toReturn;
    }

    template <typename T>
    T &myds::Deque<T>::top() {
        return _array[_headIndex];
    }
    template <typename T>
    T &myds::Deque<T>::back() {
        return _array[_tailIndex];
    }

    // Privates
    template <typename T>
    void myds::Deque<T>::_increaseCapacity(size_t increment) {
        auto oldArray = _array;
        _capacity += increment;
        _array = new T[_capacity];
        // Copy all element to old array to new array
        for (size_t i=0; i < _length; i++) {
            _array[i] = oldArray[(_headIndex + i) % _length];
        }
        // After moved values in the new array, their in a natural order starting from index 0...
        // ... and we need to reset head and tail indexes
        _headIndex = 0;
        _tailIndex = _length - 1;
        delete[] oldArray;
    }

    // Operators
    template <typename T>
    T &myds::Deque<T>::operator[](const size_t index) {
        return _array[(_headIndex + index) % _capacity];
    }
} // myds