#ifndef MY_DATA_STRUCTURES_AVLTREE_TPP
#define MY_DATA_STRUCTURES_AVLTREE_TPP

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

// ================================

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
bool myds::AVLTree<T>::isEmpty() const {
    return _root == nullptr;
}

// ==========================================================
// ===================== Visits =============================

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

#endif //MY_DATA_STRUCTURES_AVLTREE_TPP
