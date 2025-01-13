#include <exception>
#include <string>
#include <sstream>
#ifndef MY_DATA_STRUCTURES_LIST_H
#define MY_DATA_STRUCTURES_LIST_H

class IndexOutOfRangeException : public std::exception {
    private:
    size_t index;
    std::string message;

    public:
    IndexOutOfRangeException(size_t index): index(index) {
        std::string msg;
        std::stringstream ss_msg{msg};
        ss_msg << "Attempted to access index " << index << " out of range";
        message = ss_msg.str();
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

template <typename T>
class Node {
    private:
    Node* _next;

    public:
    T value;
    Node(T val);
    Node* next();
    void setNext(Node*);
};

template <typename T>
class List {
    private:
    unsigned int _length;
    Node<T> *_entry;
    Node<T> *_last;

    public:
    List();
    ~List();
    unsigned int length();
    bool empty();
    void append(T element);
    void prepend(T element);
    void insert(T element, size_t index);  // Index starts from 0
    T get(size_t index) const;
    void set(T value, size_t index);
    void remove(size_t index);

    template<typename F>
    friend std::ostream& operator<<(std::ostream& os, const List<F>& list);
    T& operator[](size_t index);
};

#include "List.tpp"

#endif //MY_DATA_STRUCTURES_LIST_H
