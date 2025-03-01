#ifndef MY_DATA_STRUCTURES_REDBLACKTREE_H
#define MY_DATA_STRUCTURES_REDBLACKTREE_H

#include <cstddef>
#include "RedBlackTreeNode.h"

namespace myds {
    template <typename T>
    class RedBlackTree {
        private:
        RedBlackTreeNode<T> *_root;
        size_t _size;
        const bool _allowDuplicates = false;
        RedBlackTree *_deepCopy(const RedBlackTreeNode<T> *);
        void _deepDelete(RedBlackTreeNode<T> *);
        bool _find(T &, RedBlackTreeNode<T> *);

        public:
        RedBlackTree();
        RedBlackTree(bool);
        RedBlackTree(const RedBlackTree &);
        ~RedBlackTree();
        bool find(T &);
    };
} // myds

#include "RedBlackTree.tpp"

#endif //MY_DATA_STRUCTURES_REDBLACKTREE_H
