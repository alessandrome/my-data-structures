#ifndef VECTORBOOL_TPP
#define VECTORBOOL_TPP

namespace myds {
    template <>
    class Vector<bool> {
        private:
        size_t _size;
        size_t _capacity;
        size_t _head; // Head index
        size_t _tail; // Tail index
        uint8_t *_array;
        void _deepCopy(const Vector &);
        void _incrementSize(size_t);

        public:
        Vector();
        Vector(size_t capacity);
        Vector(const Vector &);
        ~Vector();
        size_t length() const;
        size_t capacity() const;
        size_t byteCapacity() const;
        bool empty() const;
        bool full() const;
        void append(const bool &element);
        void prepend(const bool &element);
        void insert(const bool &element, size_t index); // Index starts from 0
        bool get(size_t index) const;
        void set(const bool &value, size_t index);
        void remove(size_t index);
        std::optional<size_t> find(const bool &);

        Vector &operator+=(const Vector &rVec);
        Vector &operator+=(const bool &rVec);
        Vector &operator=(const Vector &rVec);
        bool &operator[](size_t);

        friend std::ostream &operator<<(std::ostream &os, const Vector<bool> &rVec);
    };
} // myds

#include "VectorBool.tpp"

#endif //VECTORBOOL_TPP
