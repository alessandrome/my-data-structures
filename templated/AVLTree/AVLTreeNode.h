#ifndef MY_DATA_STRUCTURES_AVLTREENODE_H
#define MY_DATA_STRUCTURES_AVLTREENODE_H
#include <iostream>

namespace myds {
    template<typename T>
    class AVLNode {
        private:
        AVLNode *_left;
        AVLNode *_right;
        size_t _height;

        public:
        T value;
        AVLNode(T val);

        AVLNode *right();
        AVLNode *left();
        size_t height() const;

        void setLeft(AVLNode<T> *);
        void setRight(AVLNode<T> *);

        template<typename F>
        friend std::ostream &operator<<(std::ostream &os, const AVLNode<F> &node);
    };
}

#include "AVLTreeNode.tpp"

#endif //MY_DATA_STRUCTURES_AVLTREENODE_H
