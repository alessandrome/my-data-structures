#ifndef MY_DATA_STRUCTURES_DOUBLE_LINKED_LIST_H
#define MY_DATA_STRUCTURES_DOUBLE_LINKED_LIST_H
#include <cstddef>
#include <exception>
#include <string>
#include <sstream>

namespace myds {
    class IndexOutOfRangeException : public std::exception {
        private:
        size_t index;
        std::string message;

        public:
        IndexOutOfRangeException(size_t index) : index(index) {
            std::string msg;
            std::stringstream ss_msg{msg};
            ss_msg << "Attempted to access index " << index << " out of range";
            message = ss_msg.str();
        }

        const char *what() const noexcept override {
            return message.c_str();
        }
    };

    template <typename T>
    class Node {
        private:
        Node *_successor;
        Node *_predecessor;

        public:
        T value;
        Node(T val);
        Node *next();
        Node *previous();
        void setNext(Node *);
        void setPrevious(Node *);
    };

    template <typename T>
    class DoubleLinkedList {
        private:
        size_t _length;
        Node<T> *_entry;
        Node<T> *_last;

        public:
        DoubleLinkedList();
        ~DoubleLinkedList();
        size_t length() const;
        bool empty() const;
        void append(const T &element);
        void prepend(const T &element);
        void insert(const T &element, size_t index);  // Index starts from 0
        T &get(size_t index) const;
        void set(const T &value, size_t index);
        void set(T &&value, size_t index);
        void remove(size_t index);

        template <typename F>
        friend std::ostream &operator<<(std::ostream &os, const List<F> &list);
        T &operator[](size_t index);
    };
}

#include "DoubleLinkedList.tpp"

#endif //MY_DATA_STRUCTURES_DOUBLE_LINKED_LIST_H
