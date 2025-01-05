#ifndef MY_DATA_STRUCTURES_AVLTREENODE_TPP
#define MY_DATA_STRUCTURES_AVLTREENODE_TPP
#include "AVLTreeNode.h"

// NODE
template<typename T>
myds::AVLNode<T>::AVLNode(T val): value(val), _left(nullptr), _right(nullptr), _height(0) {}

template<typename T>
void myds::AVLNode<T>::setLeft(AVLNode<T> *lNode) { _left = lNode; }

template<typename T>
void myds::AVLNode<T>::setRight(AVLNode<T> *rNode) { _right = rNode; }

template<typename T>
myds::AVLNode<T> *myds::AVLNode<T>::left() { return _left; }

template<typename T>
myds::AVLNode<T> *myds::AVLNode<T>::right() { return _right; }

template<typename T>
size_t myds::AVLNode<T>::height() const { return _height; }

template<typename T>
std::ostream& operator<<(std::ostream& os, const myds::AVLNode<T>& node) { return os << node.value; }

#endif //MY_DATA_STRUCTURES_AVLTREENODE_TPP
