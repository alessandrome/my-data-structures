#include "RedBlackTree.h"

namespace myds {
    template <typename T>
    RedBlackTree<T>::RedBlackTree(): _root(nullptr), _size(0), _allowDuplicates(false) {}

    template <typename T>
    RedBlackTree<T>::RedBlackTree(const RedBlackTree &rTree): _size(rTree._size), _allowDuplicates(rTree._allowDuplicates) {
        _root = _deepCopy(rTree._root);
    }

    template <typename T>
    RedBlackTree<T>::~RedBlackTree() {
        _deepDelete(_root);
    }
} // myds
