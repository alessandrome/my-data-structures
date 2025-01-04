#ifndef MY_DATA_STRUCTURES_BSTREE_H
#define MY_DATA_STRUCTURES_BSTREE_H
#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <string>
#include <type_traits>

template <typename T>
class Node {
    private:
    Node* _left;
    Node* _right;

    public:
    T value;
    Node(T val);
    Node* right();
    Node* left();
    void setLeft(Node<T>*);
    void setRight(Node<T>*);

    template<typename F>
    friend std::ostream& operator<<(std::ostream& os, const Node<F>& node);
};

template <typename T>
class BSTree {
    static_assert(std::is_convertible_v<decltype(std::declval<T>() < std::declval<T>()), bool>, "Type T must support < operator");
    static_assert(std::is_convertible_v<decltype(std::declval<T>() == std::declval<T>()), bool>, "Type T must support == operator");

    private:
    size_t _size;
    //size_t _height;
    Node<T>* _root;
    const bool _allowDuplicates = false;
    Node<T>* _findNode(const T& value, Node<T>* root) const;
    Node<T>* _findMinNode(Node<T>* next, Node<T>* root) const;
    Node<T>* _findMaxNode(Node<T>* next, Node<T>* root) const;
    Node<T>* _inOrder(Node<T>*) const;
    void _inOrderVisit(Node<T>*) const;
    void _reverseInOrderVisit(Node<T>*) const;
    void _preOrderVisit(Node<T>*) const;
    void _postOrderVisit(Node<T>*) const;
    Node<T>* _remove(const T& value, Node<T>* root, bool& removed);
    size_t _height(Node<T>* root) const;

    public:
    BSTree();
    BSTree(bool allowDuplicates);
    // Deep Copy Constructor
    BSTree(const BSTree& other);
    Node<T>* _deepCopy(Node<T>* otherNode);
    ~BSTree();
    void _deconstruct(Node<T>* root);
    void inOrderVisit() const;
    void reverseInOrderVisit() const;
    void preOrderVisit() const;
    void postOrderVisit() const;

    void insert(T value);
    bool search(T value);
    bool remove(T value);
    bool isEmpty() const;
    size_t size() const;
    size_t height() const;
    T minValue() const;
    T maxValue() const;
    bool allowDuplicates() const;

    template<typename F>
    friend std::ostream& operator<<(std::ostream& os, const BSTree<F>& tree);
};

#include "BSTree.tpp"

#endif //MY_DATA_STRUCTURES_BSTREE_H
