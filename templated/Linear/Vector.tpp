#include <array>
#include <string>

#include "Vector.h"

namespace myds {
    template <class T>
    Vector<T>::Vector(): _size(0), _capacity(DEFAULT_VECTOR_CAPACITY), _head(0), _tail(0), _array(nullptr) {
        _array = new T[_capacity];
    }

    template <class T>
    Vector<T>::Vector(size_t capacity): _size(0), _capacity(capacity), _head(0), _tail(0) {
        _array = new T[capacity];
    }

    template <typename T>
    Vector<T>::Vector(const Vector &rVec) {
        _deepCopy(rVec);
    }

    template <typename T>
    Vector<T>::~Vector() { delete[] _array; }

    template <typename T>
    void Vector<T>::_deepCopy(const Vector &rVec) {
        _size = rVec._size;
        _capacity = rVec._capacity;
        _head = 0;
        _tail = _size % _capacity;
        _array = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _array[i] = rVec._array[(rVec._head + i) % rVec._capacity];
        }
    }

    template <typename T>
    void Vector<T>::_incrementSize(size_t increment) {
        auto oldArray = _array;
        _array = new T[_capacity + increment];
        for (size_t i = 0; i < _size; ++i) {
            _array[i] = oldArray[(_head + i) % _capacity];
        }
        delete[] oldArray;
        _head = 0;
        _tail = _size;
        _capacity += increment;
    }

    template <typename T>
    size_t Vector<T>::length() const { return _size; }

    template <typename T>
    size_t Vector<T>::capacity() const { return _capacity; }

    template <typename T>
    bool Vector<T>::empty() const { return _size == 0; }

    template <typename T>
    bool Vector<T>::full() const { return _size == _capacity; }

    template <typename T>
    void Vector<T>::append(const T &element) {
        if (_size == _capacity) {
            _incrementSize(_capacity ? _capacity : DEFAULT_VECTOR_CAPACITY);
        }
        _array[_tail] = element;
        _tail = (_tail + 1) % _capacity;
        _size++;
    }

    template <typename T>
    void Vector<T>::prepend(const T &element) {
        if (_size == _capacity) {
            _incrementSize(_capacity ? _capacity : DEFAULT_VECTOR_CAPACITY);
        }
        _head = _head == 0 ? _capacity - 1 : _head - 1;
        _array[_head] = element;
        _size++;
    }

    template <typename T>
    void Vector<T>::insert(const T &element, size_t index) {
        if (index > _size) {
            std::string msg = "Vector::insert: index ";
            msg += std::to_string(index);
            msg += " is out of range";
            throw std::out_of_range(msg);
        }
        if (_size == _capacity) {
            _incrementSize(_capacity ? _capacity : DEFAULT_VECTOR_CAPACITY);
        }

        if (index == 0) {
            // Simplify code to avoid unnecessary moving elements
            _head = _head ? _head - 1 : _capacity - 1;
            _array[_head] = element;
        } else {
            // Cycle to move all elements by one position and make space for the element to insert
            size_t circularIndex = (_head + index) % _capacity;
            size_t i = _tail;
            size_t prev = i ? i - 1 : _capacity - 1;
            while (i != circularIndex) {
                _array[i] = _array[prev];
                i = i ? i - 1 : _capacity - 1;
                prev = i ? i - 1 : _capacity - 1;
            }
            _array[circularIndex] = element;
            _tail = (_tail + 1) % _capacity;
        }
        // Update size 'n' tail
        _size++;
    }

    template <typename T>
    T &Vector<T>::get(size_t index) const {
        if (index >= _size) {
            std::string msg = "Vector::insert: index ";
            msg += std::to_string(index);
            msg += " is out of range";
            throw std::out_of_range(msg);
        }
        return _array[(_head + index) % _capacity];
    }

    template <typename T>
    void Vector<T>::set(const T &value, size_t index) {
        if (index >= _size) {
            std::string msg = "Vector::insert: index ";
            msg += std::to_string(index);
            msg += " is out of range";
            throw std::out_of_range(msg);
        }
        _array[(_head + index) % _capacity] = value;
    }

    template <typename T>
    void Vector<T>::remove(size_t index) {
        if (index >= _size) {
            std::string msg = "Vector::insert: index ";
            msg += std::to_string(index);
            msg += " is out of range";
            throw std::out_of_range(msg);
        }
        for (size_t i = index; i < _size - 1; ++i) {
            _array[(_head + i) % _capacity] = _array[(_head + i + 1) % _capacity];
        }
        _tail = (_tail + _capacity - 1) % _capacity;;
        _size--;
    }

    template <typename T>
    Vector<T> &Vector<T>::operator=(const Vector &rVec) {
        if (this != &rVec) {
            delete[] _array;
            _deepCopy(rVec);
        }
        return *this;
    }

    template <typename T>
    Vector<T> &Vector<T>::operator+=(const T &rValue) {
        append(rValue);
        return *this;
    }

    template <typename T>
    Vector<T> &Vector<T>::operator+=(const Vector &rVec) {
        // Check total size and increment array space if needed
        size_t totalSize = _size + rVec._size;
        if (totalSize > _capacity) {
            _incrementSize(rVec._capacity);
        }

        // Add element from the right Vector
        for (size_t i = 0; i < rVec._size; ++i) {
            _array[_tail] = rVec._array[(rVec._head + i) % rVec._capacity];
            _tail = (_tail + 1) % _capacity;
        }

        // Update size and return vector
        _size = totalSize;
        return *this;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Vector<T> &rVec) {
        os << '[';
        for (size_t i = 0; i < rVec._size; ++i) {
            os << rVec.get(i);
            if (i != rVec._size - 1) {
                os << ", ";
            }
        }
        os << ']';
        return os;
    }
} // myds
