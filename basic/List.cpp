#include "List.h"

// ==== Node ====
Node::Node(int val): _next(nullptr) {
    _value = val;
}

int Node::value() { return _value; }
Node* Node::next() { return _next; }
void Node::setNext(Node* next) {
    _next = next;
}

//Node::~Node() {
//
//}


// ==== List ====
List::List(): _length(0), _entry(nullptr) {}
List::~List() {
    Node* node;
    Node* next = _entry;
    for (int i=0; i < length(); i++) {
        node = next;
        next = node->next();
        delete node;
    }
}

unsigned int List::length() { return _length; }
void List::append(int element) {
    Node newNode = Node{element};
    Node* next = _entry;
}
