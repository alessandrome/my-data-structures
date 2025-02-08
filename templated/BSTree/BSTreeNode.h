#ifndef MY_DATA_STRUCTURES_BSTREENODE_H
#define MY_DATA_STRUCTURES_BSTREENODE_H
#include <iostream>

namespace myds {
    template<typename T>
    class BSTNode {
        private:
        BSTNode *_left;
        BSTNode *_right;

        public:
        T value;
        BSTNode(T val);

        BSTNode *right();

        BSTNode *left();

        void setLeft(BSTNode<T> *);

        void setRight(BSTNode<T> *);

        template<typename F>
        friend std::ostream &operator<<(std::ostream &os, const BSTNode<F> &node);
    };
}

#include "BSTreeNode.tpp"

#endif //MY_DATA_STRUCTURES_BSTREENODE_H
