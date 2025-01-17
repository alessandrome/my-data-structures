#ifndef MY_DATA_STRUCTURES_DEQUE_H
#define MY_DATA_STRUCTURES_DEQUE_H

#include <cstddef>
#include <string>
#include <sstream>
#include <exception>
#define DEFAULT_DEQUE_CAPACITY 10
#define DEFAULT_DEQUE_CAPACITY_INCREMENT 10

class DequeEmptyException : public std::exception {
    private:
    bool _front; // True if op. done ono head, otherwise on tail
    bool _pop; // True if op. done is a pop, otherwise a top/back (read only)
    std::string _message;

    public:
    DequeEmptyException(bool front, bool pop) {
        std::string msg;
        std::string frontBack = _front ? "Top" : "Back";
        std::string popRead = _pop ? "Pop"+frontBack : frontBack;
        std::stringstream ss_msg{msg};
        ss_msg << "Attempted to " << popRead << " on "  << frontBack;
        _message = ss_msg.str();
    }
    const char *what() const noexcept override {
        return "Attempted to access top or pop from an empty stack";
    }
};

namespace myds {
    template <typename T>
    class Deque {
        private:
        size_t _capacity;
        size_t _length;
        T *_array;
        size_t _headIndex;
        size_t _tailIndex;
        void _increaseCapacity(size_t increment);

        public:
        Deque();
        Deque(size_t startingCapacity);
        ~Deque();
        size_t length() const;
        bool empty() const;
        void pushFront(const T &value);
        void pushBack(const T &value);
        T popBack();
        T popFront();
        T &back();
        T &top();
        T &operator[](const size_t);
    };
} // myds

#include "Deque.tpp"

#endif //MY_DATA_STRUCTURES_DEQUE_H
