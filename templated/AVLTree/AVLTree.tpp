#ifndef MY_DATA_STRUCTURES_AVLTREE_TPP
#define MY_DATA_STRUCTURES_AVLTREE_TPP

#include "AVLTree.h"

template<typename T>
myds::AVLTree<T>::AVLTree(): _root(nullptr), _size(0), _allowDuplicates(false) {}

template<typename T>
myds::AVLTree<T>::AVLTree(bool allowDuplicates): _root(nullptr), _size(0), _allowDuplicates(allowDuplicates) {}

template<typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_insert(const T &value, AVLNode<T> *root) {
    if (root == nullptr) {
        return new AVLNode<T>(value);
    }
    if (root->value == value && !_allowDuplicates) {
        return root;
    }
    if (value < root->value) {
        root->setLeft(_insert(value, root->left()));
    } else {
        root->setRight(_insert(value, root->right()));
    }
}

template<typename T>
myds::AVLNode<T>* myds::AVLTree<T>::_leftRotate(AVLNode<T> *root) {
    // A->B->C to A<-B->C
    AVLNode<T>* newRoot = root->right();
    root->setRight(newRoot->left());
    newRoot->setLeft(root);

    // Updating height of nodes (from bottom to top)
    root->updateHeight();
    newRoot->updateHeight();
    return newRoot;
}

template<typename T>
myds::AVLNode<T>* myds::AVLTree<T>::_rightRotate(AVLNode<T> *root) {
    // C<-B<-A to C<-B->A
    AVLNode<T>* newRoot = root->left();
    root->setLeft(newRoot->right());
    newRoot->setRight(root);

    // Updating height of nodes (from bottom to top)
    root->updateHeight();
    newRoot->updateHeight();
    return newRoot;
}

template<typename T>
void myds::AVLTree<T>::insert(T value) {
    _insert(value);
}

#endif //MY_DATA_STRUCTURES_AVLTREE_TPP
