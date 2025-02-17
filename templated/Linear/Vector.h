#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

namespace myds {
    template <typename T>
    class Vector {
        private:
        size_t _size;
        size_t _capacity;
		size_t _head;  // Head index
		size_t _tail;  // Tail index
        T *data;

        public:
        Vector();
        Vector(size_t capacity);
        ~Vector();
		size_t length() const;
    	bool empty() const;
    	void append(const T &element);
    	void prepend(const T &element);
    	void insert(const T &element, size_t index);  // Index starts from 0
    	T& get(size_t index) const;
    	void set(const T& value, size_t index);
    	void remove(size_t index);
    };
} // myds

#include "Vector.tpp"

#endif //VECTOR_H
