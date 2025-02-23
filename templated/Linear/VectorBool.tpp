#include "VectorBool.h"

namespace myds {
    Vector<bool>::Vector(): _array(nullptr), _size(0), _capacity(DEFAULT_VECTOR_CAPACITY / 8 * 8), _head(0), _tail(0) {
        _array = new uint8_t[_capacity];
    }

    Vector<bool>::Vector(size_t capacity): _array(nullptr), _size(0), _capacity(capacity / 8 * 8), _head(0), _tail(0) {
        _array = new uint8_t[capacity];
    }

    Vector<bool>::Vector(const Vector &rVec) { _deepCopy(rVec); }

    Vector<bool>::~Vector() { delete[] _array; }

    void Vector<bool>::_deepCopy(const Vector &rVec) {
        _size = rVec._size;
        _capacity = rVec._capacity;
        _array = new uint8_t[_capacity];
        std::memcpy(_array, rVec._array, _capacity);
    }

    void Vector<bool>::_incrementSize(size_t increment) {
        auto oldArray = _array;
        _array = new uint8_t[_capacity + increment];
        std::memcpy(_array, oldArray, _capacity);
        delete[] oldArray;
        _capacity += increment;
    }

    size_t Vector<bool>::length() const { return _size; }

    size_t Vector<bool>::capacity() const { return _capacity * 8; }

    size_t Vector<bool>::byteCapacity() const { return _capacity; }

    bool Vector<bool>::empty() const { return _size == 0; }

    bool Vector<bool>::full() const { return _size == _capacity * 8; }

    inline void Vector<bool>::append(const bool &element) {
        if (_size / 8 == _capacity) {
            _incrementSize(_capacity);
        }
        uint8_t bitMask = 1 << (_tail % 8);
        if (element) {
            _array[_tail / 8] = element;
        } else {

        }
        _size++;
    }
} // myds
