#ifndef MY_DATA_STRUCTURES_AVLTREE_TPP
#define MY_DATA_STRUCTURES_AVLTREE_TPP

#include <iostream>
#include "AVLTree.h"

template <typename T>
myds::AVLTree<T>::AVLTree(): _root(nullptr), _size(0), _allowDuplicates(false) {}

template <typename T>
myds::AVLTree<T>::AVLTree(bool allowDuplicates): _root(nullptr), _size(0), _allowDuplicates(allowDuplicates) {}

template <typename T>
myds::AVLTree<T>::~AVLTree() {
    _deconstruct(_root);
}

template <typename T>
void myds::AVLTree<T>::_deconstruct(AVLNode<T> *root) {
    if (!root) return;
    _deconstruct(root->left());
    _deconstruct(root->right());
    delete root;
}

template <typename T>
myds::AVLTree<T>::AVLTree(const AVLTree<T> &other): _allowDuplicates(other._allowDuplicates) {
    _root = _deepCopy(other._root);
    _size = other._size;
}

template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_deepCopy(AVLNode<T> *otherNode) {
    if (!otherNode) return nullptr;

    auto *newNode = new AVLNode<T>(otherNode->value);
    newNode->setLeft(_deepCopy(otherNode->left()));
    newNode->setRight(_deepCopy(otherNode->right()));
    return newNode;
}

// ========= Find methods ==========
template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_findNode(const T &value, AVLNode<T> *root) const {
    // Check if there is a valid root for the subtree
    if (!root) return nullptr;

    // Check if root contains wanted value
    if (root->value == value) return root;

    if (value < root->value) {
        return _findNode(value, root->left());
    }
    return _findNode(value, root->right());
}

template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_findMinNode(AVLNode<T> *root) const {
    // Check if there is a valid root for the subtree
    if (!root) return nullptr;

    while (root->left()) {
        root = root->left();
    }
    return root;
}

template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_findMaxNode(AVLNode<T> *root) const {
    // Check if there is a valid root for the subtree
    if (!root) return nullptr;

    while (root->right()) {
        root = root->right();
    }
    return root;
}

template <typename T>
T myds::AVLTree<T>::minValue() const {
    if (!_root) throw myds::TreeEmptyException("AVLTree::minValue()");
    return _findMinNode(_root)->value;
}

template <typename T>
T myds::AVLTree<T>::maxValue() const {
    if (!_root) throw myds::TreeEmptyException("AVLTree::maxValue()");
    return _findMaxNode(_root)->value;
}

template <typename T>
size_t myds::AVLTree<T>::_height(AVLNode<T> *root) const {
    if (!root) return 0;
    return 1 + std::max(
            _height(root->left()),
            _height(root->right())
            );
}

// ================================================================

template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_insert(const T &value, AVLNode<T> *root) {
    if (root == nullptr) {
        _size++;
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

    root->updateHeight();
    int balance = root->balance();

    // Caso 1: Left-Left
    if (balance > 1 && root->left() && value < root->left()->value)
        return _rightRotate(root);

    // Caso 2: Right-Right
    if (balance < -1 && root->right() && value > root->right()->value)
        return _leftRotate(root);

    // Caso 3: Left-Right
    if (balance > 1 && root->left() && value > root->left()->value) {
        root->setLeft(_leftRotate(root->left()));
        return _rightRotate(root);
    }

    // Caso 4: Right-Left
    if (balance < -1 && root->right() && value < root->right()->value) {
        root->setRight(_rightRotate(root->right()));
        return _leftRotate(root);
    }

    // Return current root node of analyzed subtree
    return root;
}

template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_leftRotate(AVLNode<T> *root) {
    // A->B->C to A<-B->C
    AVLNode<T> *newRoot = root->right();
    root->setRight(newRoot->left());
    newRoot->setLeft(root);

    // Updating height of nodes (from bottom to top)
    root->updateHeight();
    newRoot->updateHeight();
    return newRoot;
}

template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_rightRotate(AVLNode<T> *root) {
    // C<-B<-A to C<-B->A
    AVLNode<T> *newRoot = root->left();
    root->setLeft(newRoot->right());
    newRoot->setRight(root);

    // Updating height of nodes (from bottom to top)
    root->updateHeight();
    newRoot->updateHeight();
    return newRoot;
}

template <typename T>
void myds::AVLTree<T>::insert(const T &value) {
    _root = _insert(value, _root);
}

template <typename T>
bool myds::AVLTree<T>::search(const T &value) {
    auto searchRoot = _root;
    while (searchRoot) {
        if (value == searchRoot->value) return true;
        searchRoot = value < searchRoot->value ? searchRoot->left() : searchRoot->right();
    }
    return false;
}

template <typename T>
myds::AVLNode<T> *myds::AVLTree<T>::_remove(const T &value, AVLNode<T> *root, bool &removed) {
    if (!root) return nullptr;
    if (value < root->value) {
        root->setLeft(_remove(value, root->left(), removed));
    } else if (value > root->value) {
        root->setRight(_remove(value, root->right(), removed));
    } else {
        removed = true;

        // Case 1: No node's children
        if (!root->left() && !root->right()) {
            delete root;
            return nullptr;
        }

        // Case : Just 1 child
        if (!root->left()) {
            AVLNode<T>* temp = root->right();
            delete root;
            return temp;
        } else if (!root->right()) {
            AVLNode<T>* temp = root->left();
            delete root;
            return temp;
        }

        // Case 3: Two children
        AVLNode<T>* successor = _findMinNode(root->right());  // Get the successor of removed element
        root->value = successor->value;  // Replace current node with value to remove with its successor value
        root->setRight(_remove(successor->value, root->right(), removed));  // Remove the sub-node that contain successor of the removed one
    }

    // Update height of the node and then apply rotations (if needed)
    root->updateHeight();
    int balance = root->balance();

    // **Left Heavy** (balance > 1)
    if (balance > 1) {
        if (root->left()->balance() >= 0) {
            return _rightRotate(root); // R - Rotate
        } else {
            root->setLeft(_leftRotate(root->left())); // LR - Rotate
            return _rightRotate(root);
        }
    }

    // **Right Heavy** (balance < -1)
    if (balance < -1) {
        if (root->right()->balance() <= 0) {
            return _leftRotate(root); // L - Rotate
        } else {
            root->setRight(_rightRotate(root->right())); // RL - Rotate
            return _leftRotate(root);
        }
    }

    return root;
}

template <typename T>
bool myds::AVLTree<T>::remove(const T &value) {
    bool removed = false;
    _root = _remove(value, _root, removed);
    if (removed) _size--;
    return removed;
}

template <typename T>
size_t myds::AVLTree<T>::size() const {
    return _size;
}

template <typename T>
size_t myds::AVLTree<T>::height() const {
    return _root ? _root->height() : 0;
}

template <typename T>
bool myds::AVLTree<T>::isEmpty() const {
    return _root == nullptr;
}

template <typename T>
bool myds::AVLTree<T>::allowDuplicates() const {
    return _allowDuplicates;
}

// ==========================================================
// ===================== Visits =============================

template <typename T>
void myds::AVLTree<T>::_inOrderVisit(AVLNode<T> *root) const {
    if (!root) return;
    _inOrderVisit(root->left());
    std::cout << std::setw(5) << root->value;
    _inOrderVisit(root->right());
}
template <typename T>
void myds::AVLTree<T>::_reverseInOrderVisit(AVLNode<T> *root) const {
    if (!root) return;
    _reverseInOrderVisit(root->right());
    std::cout << std::setw(5) << root->value;
    _reverseInOrderVisit(root->left());
}
template <typename T>
void myds::AVLTree<T>::_preOrderVisit(AVLNode<T> *root) const {
    if (!root) return;
    std::cout << std::setw(5) << root->value;
    _preOrderVisit(root->left());
    _preOrderVisit(root->right());
}
template <typename T>
void myds::AVLTree<T>::_postOrderVisit(AVLNode<T> *root) const {
    if (!root) return;
    _postOrderVisit(root->left());
    _postOrderVisit(root->right());
    std::cout << std::setw(5) << root->value;
}

template <typename T>
void myds::AVLTree<T>::inOrderVisit() const {
    _inOrderVisit(_root);
}
template <typename T>
void myds::AVLTree<T>::reverseInOrderVisit() const {
    _reverseInOrderVisit(_root);
}
template <typename T>
void myds::AVLTree<T>::preOrderVisit() const {
    _preOrderVisit(_root);
}
template <typename T>
void myds::AVLTree<T>::postOrderVisit() const {
    _postOrderVisit(_root);
}

template <typename T>
void myds::AVLTree<T>::_inOrderValues(AVLNode<T> *root, T* arr, size_t &pos) const {
    if (!root) return;
    _inOrderValues(root->left(), arr, pos);
    arr[pos++] = root->value;
    _inOrderValues(root->right(), arr, pos);
}
template <typename T>
[[nodiscard]] T *myds::AVLTree<T>::inOrderValues() const {
    T *values = new T[_size];
    size_t pos = 0;
    _inOrderValues(_root, values, pos);
    return values;
}

template <typename T>
void myds::AVLTree<T>::_preOrderValues(AVLNode<T> *root, T* arr, size_t &pos) const {
    if (!root) return;
    arr[pos++] = root->value;
    _postOrderValues(root->left(), arr, pos);
    _postOrderValues(root->right(), arr, pos);
}
template <typename T>
[[nodiscard]] T *myds::AVLTree<T>::preOrderValues() const {
    T *values = new T[_size];
    size_t pos = 0;
    _preOrderValues(_root, values, pos);
    return values;
}

template <typename T>
void myds::AVLTree<T>::_postOrderValues(AVLNode<T> *root, T* arr, size_t &pos) const {
    if (!root) return;
    _postOrderValues(root->left(), arr, pos);
    _postOrderValues(root->right(), arr, pos);
    arr[pos++] = root->value;
}
template <typename T>
[[nodiscard]] T *myds::AVLTree<T>::postOrderValues() const {
    T *values = new T[_size];
    size_t pos = 0;
    _postOrderValues(_root, values, pos);
    return values;
}

// ==========================================================
// ===================== Friend =============================

template <typename T>
std::ostream &operator<<(std::ostream &os, const myds::AVLTree<T> &tree) {
    // Get array of ordered values - Space Complexity O(N)
    auto values = tree.inOrderValues();
    size_t size = tree.size();
    std::string msg;
    std::stringstream ss_msg{msg};
    ss_msg << "[";
    for (int i=0; i<size; i++) {
        ss_msg << values[i];
        if (i != size - 1) {
            ss_msg << ", ";
        }
    }
    ss_msg << "]";
    delete[] values;
    return os << msg;
}

#endif //MY_DATA_STRUCTURES_AVLTREE_TPP
