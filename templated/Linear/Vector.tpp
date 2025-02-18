#include "Vector.h"

namespace myds {
    template <class T>
    Vector<T>::Vector(): _size(0), _capacity(0), _head(0), _tail(0), _array(nullptr) {}
    template <class T>
    Vector<T>::Vector(size_t capacity): _size(0), _capacity(capacity), _head(0), _tail(0) {
        _array = new T[capacity];
    }
    template <typename T>
    Vector<T>::Vector(const Vector& rVec) {
        _deepCopy(rVec);
    }

    template <typename T>
    Vector<T>::~Vector() { delete[] _array; }

    template <typename T>
    void Vector<T>::_deepCopy(const Vector& rVec) {
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
    size_t Vector<T>::length() const { return _size; }

    template<typename T>
    bool Vector <T>::empty() const { return _size == 0; }


    template <typename T>
    Vector<T> &Vector<T>::operator=(const Vector &rVec) {
        if (this != &rVec) {
            delete[] _array;
            _deepCopy(rVec);
        }
        return *this;
    }

} // myds
