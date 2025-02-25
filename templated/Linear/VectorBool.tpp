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
        // TODO: memcpy wrong-> correct reordering (whem _head > _tail)
        delete[] oldArray;
        _capacity += increment;
    }

    size_t Vector<bool>::length() const { return _size; }

    size_t Vector<bool>::capacity() const { return _capacity * 8; }

    size_t Vector<bool>::byteCapacity() const { return _capacity; }

    bool Vector<bool>::empty() const { return _size == 0; }

    bool Vector<bool>::full() const { return _size == _capacity * 8; }

    void Vector<bool>::append(const bool &element) {
        if (_size / 8 == _capacity) {
            _incrementSize(_capacity);
        }
        uint8_t bitMask = 1 << (_tail % 8);
        if (element) {
            _array[_tail / 8] |= bitMask;
        } else {
            _array[_tail / 8] &= ~bitMask;
        }
        _tail = (_tail + 1) % (_capacity * 8);
        _size++;
    }

    void Vector<bool>::prepend(const bool &element) {
        if (_size / 8 == _capacity) {
            _incrementSize(_capacity);
        }
        _head = (_head + _capacity * 8 - 1) % (_capacity * 8);
        uint8_t bitMask = 1 << (_head % 8);
        if (element) {
            _array[_head / 8] |= bitMask;
        } else {
            _array[_head / 8] &= ~bitMask;
        }
        _size++;
    }

    bool Vector<bool>::get(size_t index) const {
        if (index >= _size) {
            std::string msg = "Vector index ";
            msg += std::to_string(index);
            msg += " is out of bounds! (length is ";
            msg += std::to_string(_size);
            msg += ")";
            throw std::out_of_range(msg);
        }
        size_t internalIndex = (_head + index) % (_capacity * 8);
        uint8_t bitMask = 1 << (internalIndex % 8);
        return (_array[internalIndex / 8] & bitMask) != 0;
    }
} // myds
