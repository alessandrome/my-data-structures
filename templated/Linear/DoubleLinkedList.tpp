#include "DoubleLinkedList.h"

// ==== Node ====
template <typename T>
myds::Node<T>::Node(T val): value(val), _successor(nullptr), _predecessor(nullptr) {}

template <typename T>
myds::Node<T>* myds::Node<T>::next() { return _successor; }
template <typename T>
myds::Node<T>* myds::Node<T>::previous() { return _predecessor; }

template <typename T>
void myds::Node<T>::setNext(Node* next) {
    _successor = next;
}
template <typename T>
void myds::Node<T>::setPrevious(Node* next) {
    _predecessor = next;
}


// ==== List ====
template <typename T>
myds::DoubleLinkedList<T>::DoubleLinkedList(): _length(0), _entry(nullptr), _last(nullptr) {}

template <typename T>
myds::DoubleLinkedList<T>::~DoubleLinkedList() {
    Node<T>* current = _entry;
    Node<T>* next;
    while (current != nullptr) {
        next = current->next();
        delete current;
        current = next;
    }
}

template <typename T>
size_t myds::DoubleLinkedList<T>::length() const { return _length; }

template <typename T>
bool myds::DoubleLinkedList<T>::empty() const { return _length == 0; }

template <typename T>
void myds::DoubleLinkedList<T>::append(const T &element) {
    Node<T>* newNode = new Node<T>{element};
    if (_last != nullptr) {
        _last->setNext(newNode);
        newNode->setPrevious(_last);
    } else {
        _entry = newNode;
    }
    _last = newNode;
    _length++;
}

template <typename T>
void myds::DoubleLinkedList<T>::prepend(const T &element) {
    auto newNode = new Node<T>{element};  // "auto" keyword automatically predict type by done operation
    if (_entry != nullptr) {
        _entry->setPrevious(newNode);
        newNode->setNext(_entry);
    } else {
        _last = newNode;
    }
    _entry = newNode;
    _length++;
}

template<typename T>
void myds::DoubleLinkedList<T>::insert(const T &element, size_t index) {
    if (index > _length) {
        throw IndexOutOfRangeException(index);
    }
    if (index == _length) {
        append(element);
    } else if (index == 0) {
        prepend(element);
    } else {
        auto newNode = new Node<T>{element};
        auto prev = _entry;
        for (size_t i = 0; i < index - 1; i++) {
            prev = prev->next();
        }
        auto next = prev->next();
        newNode->setNext(next);
        newNode->setPrevious(prev);
        prev->setNext(newNode);
        next->setPrevious(newNode);
        _length++;
    }
}


template<typename T>
T& myds::DoubleLinkedList<T>::get(size_t index) const {
    if (index >= _length) {
        throw IndexOutOfRangeException(index);
    }
    if (index == _length - 1) {
        // Simply return value in the _last node
        return _last->value;
    }
    auto actual = _entry;
    for (size_t i = 0; i < index; i++) {
        actual = actual->next();
    }
    return actual->value;
}

template<typename T>
void myds::DoubleLinkedList<T>::set(const T& value, size_t index) {
    if (index >= _length) {
        throw IndexOutOfRangeException(index);
    }
    if (index == _length - 1) {
        // Simply set the value in the _last node
        _last->value = value;
    } else {
        // Else iterate through the list to reach the index positioned Node<T>
        auto actual = _entry;
        for (size_t i = 0; i < index; i++) {
            actual = actual->next();
        }
        actual->value = value;
    }
}

template<typename T>
void myds::DoubleLinkedList<T>::remove(size_t index) {
    if (index >= _length) {
        throw IndexOutOfRangeException(index);
    }
    Node<T>* predecessorNode = nullptr; // Will contain predecessor of node to remove
    auto toRemoveNode = _entry; // Will contain node to remove
    // Iterate through the list
    for (size_t i = 0; i < index; i++) {
        predecessorNode = toRemoveNode;
        toRemoveNode = toRemoveNode->next();
    }
    // Retrieve next node of node to remove
    auto nextNode = toRemoveNode->next();

    if (predecessorNode != nullptr) {
        // The node to remove is NOT the head: set its successor as the next to the node to remove
        predecessorNode->setNext(nextNode);
    } else {
        // The node to remove IS the head: replace entry point of the list with successor of the node to remove
        _entry = toRemoveNode->next();
        toRemoveNode->next()->setPrevious(nullptr);
    };
    if (nextNode != nullptr) nextNode->setPrevious(predecessorNode); // If next exists, update its predecessor
    if (_last == toRemoveNode) _last = predecessorNode; // If the node to remove is the last one, update _last pointer
    delete toRemoveNode;
    _length--;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const myds::DoubleLinkedList<T>& list) {
    os << "[";
    for (auto node=list._entry; node != nullptr; node=node->next()) {
        os << node->value;
        if (node->next() != nullptr) os << ", ";
    }
    os << "]";
    return os;
}


template<typename T>
T& myds::DoubleLinkedList<T>::operator[](size_t index) {
    // Same behavior of the get(index) method
    return get(index);
}
