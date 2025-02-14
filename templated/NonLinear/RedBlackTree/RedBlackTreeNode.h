#ifndef MY_DATA_STRUCTURES_REDBLACKTREENODE_H
#define MY_DATA_STRUCTURES_REDBLACKTREENODE_H

namespace myds {
    template<typename T>
    class RedBlackTreeNode {
        private:
        RedBlackTreeNode *_left;
        RedBlackTreeNode *_right;

        public:
        T value;
        RedBlackTreeNode(T &value);
        RedBlackTreeNode *left() const;
        RedBlackTreeNode *right() const;
        void setLeft(RedBlackTreeNode *);
        void setRight(RedBlackTreeNode *);
    };
}

#include "RedBlackTreeNode.tpp"

#endif //MY_DATA_STRUCTURES_REDBLACKTREENODE_H
