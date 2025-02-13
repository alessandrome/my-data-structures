#ifndef MY_DATA_STRUCTURES_AVLTREE_H
#define MY_DATA_STRUCTURES_AVLTREE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <string>
#include <type_traits>
#include "../TreeEmptyException.h"
#include "AVLTreeNode.h"

namespace myds {
    template <typename T>
    class AVLTree {
        static_assert(std::is_convertible_v<decltype(std::declval<T>() < std::declval<T>()), bool>,
                      "Type T must support < operator");
        static_assert(std::is_convertible_v<decltype(std::declval<T>() == std::declval<T>()), bool>,
                      "Type T must support == operator");

        private:
        size_t _size;
        //size_t _height;
        AVLNode<T> *_root;
        const bool _allowDuplicates = false;

        void _deconstruct(AVLNode<T> *root);
        AVLNode<T> *_deepCopy(AVLNode<T> *otherNode);
        AVLNode<T> *_findNode(const T &value, AVLNode<T> *root) const;

        AVLNode<T> *_findMinNode(AVLNode<T> *root) const;
        AVLNode<T> *_findMaxNode(AVLNode<T> *root) const;

        void _inOrderVisit(AVLNode<T> *) const;
        void _reverseInOrderVisit(AVLNode<T> *) const;
        void _preOrderVisit(AVLNode<T> *) const;
        void _postOrderVisit(AVLNode<T> *) const;
        void _inOrderValues(AVLNode<T>*, T*, size_t&) const;
        void _preOrderValues(AVLNode<T>*, T*, size_t&) const;
        void _postOrderValues(AVLNode<T>*, T*, size_t&) const;

        AVLNode<T> *_insert(const T &value, AVLNode<T> *root);
        AVLNode<T> *_remove(const T &value, AVLNode<T> *root, bool &removed);
        size_t _height(AVLNode<T> *root) const;

        AVLNode<T> *_leftRotate(AVLNode<T> *root);
        AVLNode<T> *_rightRotate(AVLNode<T> *root);

        public:
        AVLTree();
        AVLTree(bool allowDuplicates);
        // Deep Copy Constructor
        AVLTree(const AVLTree &other);

        ~AVLTree();
        void inOrderVisit() const;
        void reverseInOrderVisit() const;
        void preOrderVisit() const;
        void postOrderVisit() const;
        [[nodiscard]] T *inOrderValues() const;
        [[nodiscard]] T *preOrderValues() const;
        [[nodiscard]] T *postOrderValues() const;
        void insert(const T &value);
        bool search(const T &value);
        bool remove(const T &value);
        bool isEmpty() const;
        size_t size() const;
        size_t height() const;
        T minValue() const;
        T maxValue() const;
        bool allowDuplicates() const;

        template <typename F>
        friend std::ostream &operator<<(std::ostream &os, const AVLTree<F> &tree);
    };

#include "AVLTree.tpp"

}

#endif //MY_DATA_STRUCTURES_AVLTREE_H
