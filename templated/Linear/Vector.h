#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstddef>

namespace myds {
    constexpr size_t DEFAULT_VECTOR_CAPACITY = 8;

    template <typename T>
    class Vector {
        private:
        size_t _size{};
        size_t _capacity{};
        size_t _head{}; // Head index
        size_t _tail{}; // Tail index
        T *_array;
        void _deepCopy(const Vector &);
        void _incrementSize(size_t);

        public:
        Vector();
        Vector(size_t capacity);
        Vector(const Vector &);
        ~Vector();
        size_t length() const;
        size_t capacity() const;
        bool empty() const;
        bool full() const;
        void append(const T &element);
        void prepend(const T &element);
        void insert(const T &element, size_t index); // Index starts from 0
        T &get(size_t index) const;
        void set(const T &value, size_t index);
        void remove(size_t index);

        Vector &operator+=(const Vector &rVec);
        Vector &operator+=(const T &rVec);
        Vector &operator=(const Vector &rVec);

        template<typename F>
        friend std::ostream &operator<<(std::ostream &os, const Vector<F> &rVec);
    };
} // myds

#include "Vector.tpp"

#endif //VECTOR_H
