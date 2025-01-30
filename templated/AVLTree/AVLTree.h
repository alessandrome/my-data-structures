#ifndef MY_DATA_STRUCTURES_AVLTREE_H
#define MY_DATA_STRUCTURES_AVLTREE_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <exception>
#include <string>
#include <type_traits>
#include "AVLTreeNode.h"

namespace myds {
    class TreeEmptyException : public std::exception {
        private:
        bool _front; // True if op. done ono head, otherwise on tail
        bool _pop; // True if op. done is a pop, otherwise a top/back (read only)
        std::string _message;

        public:
        TreeEmptyException(std::string functionName) {
            std::string msg;
            std::stringstream ss_msg{msg};
            ss_msg << "Attempted to  us \"" << functionName << "\" on empty Tree";
            _message = ss_msg.str();
        }
        const char *what() const noexcept override {
            return _message.c_str();
        }
    };

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
        AVLNode<T> *_inOrder(AVLNode<T> *) const;

        void _inOrderVisit(AVLNode<T> *) const;
        void _reverseInOrderVisit(AVLNode<T> *) const;
        void _preOrderVisit(AVLNode<T> *) const;
        void _postOrderVisit(AVLNode<T> *) const;

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
        void insert(T &value);
        bool search(const T &value);
        bool remove(T &value);
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
