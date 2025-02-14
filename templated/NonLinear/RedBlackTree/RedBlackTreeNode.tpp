#include "RedBlackTreeNode.h"

template <typename T>
myds::RedBlackTreeNode<T>::RedBlackTreeNode(T &val): value(val), _left(nullptr), _right(nullptr) {}

template <typename T>
myds::RedBlackTreeNode<T> *myds::RedBlackTreeNode<T>::left() const { return _left; }
template <typename T>
myds::RedBlackTreeNode<T> *myds::RedBlackTreeNode<T>::right() const { return _right; }

template <typename T>
void myds::RedBlackTreeNode<T>::setLeft(RedBlackTreeNode *node) { _left = node; }
template <typename T>
void myds::RedBlackTreeNode<T>::setRight(RedBlackTreeNode *node) { _right = node; }
