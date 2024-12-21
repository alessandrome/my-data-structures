#ifndef MY_DATA_STRUCTURES_LIST_H
#define MY_DATA_STRUCTURES_LIST_H


class Node {
    private:
    int _value;
    Node* _next;

    public:
    Node();
    ~Node();
    int value();
    Node* next();
};

class List {
    private:
    unsigned int _length;

    public:
    List();
    unsigned int length();
    void append(int element);
    void prepend(int element);
    void insert(int element, int index);
    int get(int index);
    void remove(int index);
};


#endif //MY_DATA_STRUCTURES_LIST_H
