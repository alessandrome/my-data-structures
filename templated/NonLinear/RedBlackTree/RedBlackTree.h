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

        public:
        RedBlackTree();
        RedBlackTree(const RedBlackTree&);
        ~RedBlackTree();
    };

} // myds

#include "RedBlackTree.tpp"

#endif //MY_DATA_STRUCTURES_REDBLACKTREE_H
