#ifndef MY_DATA_STRUCTURES_BSTREE_TPP
#define MY_DATA_STRUCTURES_BSTREE_TPP
#include "BSTreeNode.h"

// NODE
template<typename T>
myds::BSTNode<T>::BSTNode(T val): value(val), _left(nullptr), _right(nullptr) {}

template<typename T>
void myds::BSTNode<T>::setLeft(BSTNode<T> *lNode) { _left = lNode; }

template<typename T>
void myds::BSTNode<T>::setRight(BSTNode<T> *rNode) { _right = rNode; }

template<typename T>
myds::BSTNode<T> *myds::BSTNode<T>::left() { return _left; }

template<typename T>
myds::BSTNode<T> *myds::BSTNode<T>::right() { return _right; }

template<typename T>
std::ostream& operator<<(std::ostream& os, const myds::BSTNode<T>& node) { return os << node.value; }

#endif //MY_DATA_STRUCTURES_BSTREE_TPP
