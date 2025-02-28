#include "RedBlackTree.h"

namespace myds {
    template <typename T>
    RedBlackTree<T>::RedBlackTree(): _root(nullptr), _size(0), _allowDuplicates(false) {}

    template <typename T>
    RedBlackTree<T>::RedBlackTree(bool allowDuplicates): _root(nullptr), _size(0), _allowDuplicates(true) {}

    template <typename T>
    RedBlackTree<T>::RedBlackTree(const RedBlackTree &rTree): _size(rTree._size), _allowDuplicates(rTree._allowDuplicates) {
        _root = _deepCopy(rTree._root);
    }

    template <typename T>
    RedBlackTree<T>::~RedBlackTree() {
        _deepDelete(_root);
    }

    template <typename T>
    RedBlackTree<T> *RedBlackTree<T>::_deepCopy(const RedBlackTreeNode<T> *root) {
        if (!root) return nullptr;
        _deepCopy(root->left());
        _deepCopy(root->right());
        return root;
    }

    template <typename T>
    void RedBlackTree<T>::_deepDelete(RedBlackTreeNode<T> *root) {
        if (!root) return;
        _deepDelete(root->left());
        _deepDelete(root->right());
        delete root;
    }
} // myds
