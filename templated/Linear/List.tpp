#include "List.h"

// ==== Node ====
template <typename T>
Node<T>::Node(T val): value(val), _next(nullptr) {}

template <typename T>
Node<T>* Node<T>::next() { return _next; }

template <typename T>
void Node<T>::setNext(Node* next) {
    _next = next;
}


// ==== List ====
template <typename T>
List<T>::List(): _length(0), _entry(nullptr), _last(nullptr) {}

template <typename T>
List<T>::~List() {
    Node<T>* current = _entry;
    Node<T>* next;
    while (current != nullptr) {
        next = current->next();
        delete current;
        current = next;
    }
}

template <typename T>
size_t List<T>::length() const { return _length; }

template <typename T>
bool List<T>::empty() const { return _length == 0; }

template <typename T>
void List<T>::append(T element) {
    Node<T>* oldLast = _last;
    Node<T>* newNode = new Node<T>{element};
    if (oldLast != nullptr) {
        oldLast->setNext(newNode);
    } else {
        _entry = newNode;
    }
    _last = newNode;
    _length++;
}

template <typename T>
void List<T>::prepend(T element) {
    Node<T>* oldEntry = _entry;
    auto newNode = new Node<T>{element};  // "auto" keyword automatically predict type by done operation
    if (oldEntry != nullptr) {
        newNode->setNext(oldEntry);
    } else {
        _last = newNode;
    }
    _entry = newNode;
    _length++;
}

template<typename T>
void List<T>::insert(T element, size_t index) {
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
        auto actual = prev->next();
        for (size_t i = 1; i < index; i++) {
            prev = actual;
            actual = actual->next();
        }
        prev->setNext(newNode);
        newNode->setNext(actual);
        _length++;
    }
}


template<typename T>
T& List<T>::get(size_t index) const {
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
void List<T>::set(T& value, size_t index) {
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
void List<T>::remove(size_t index) {
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
    if (predecessorNode != nullptr) {
        // The node to remove is NOT the head: set its successor as the next to the node to remove
        predecessorNode->setNext(toRemoveNode->next());
    } else {
        // The node to remove IS the head: replace entry point of the list with successor of the node to remove
        _entry = toRemoveNode->next();
    };
    if (_last == toRemoveNode) _last = predecessorNode; // If the node to remove is the last one, update _last pointer
    delete toRemoveNode;
    _length--;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    os << "[";
    for (auto node=list._entry; node != nullptr; node=node->next()) {
        os << node->value;
        if (node->next() != nullptr) os << ", ";
    }
    os << "]";
    return os;
}


template<typename T>
T& List<T>::operator[](size_t index) {
    // Same behavior of the get(index) method
    return get(index);
}
