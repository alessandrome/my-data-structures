#ifndef MY_DATA_STRUCTURES_BSTREE_TPP
#define MY_DATA_STRUCTURES_BSTREE_TPP

#include <exception>
#include "BSTree.h"

class EmptyTreeException : public std::exception {
    private:
    std::string message;

    public:
    EmptyTreeException() {
        std::string msg;
        std::stringstream ss_msg{msg};
        ss_msg << "Attempted to access an empty Tree";
        message = ss_msg.str();
    }
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// NODE
template<typename T>
Node<T>::Node(T val): value(val), _left(nullptr), _right(nullptr) {}

template<typename T>
void Node<T>::setLeft(Node<T> *lNode) { _left = lNode; }

template<typename T>
void Node<T>::setRight(Node<T> *rNode) { _right = rNode; }

template<typename T>
Node<T> *Node<T>::left() { return _left; }

template<typename T>
Node<T> *Node<T>::right() { return _right; }

template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node) { return os << node.value; }


// BSTREE
template<typename T>
BSTree<T>::BSTree(): _root(nullptr), _size(0) {}
// BSTREE Copy Constructor
template<typename T>
BSTree<T>::BSTree(const BSTree& other): _allowDuplicates(other._allowDuplicates) {
    _root = _deepCopy(other._root);
    _size = other._size;
}
template<typename T>
Node<T>* BSTree<T>::_deepCopy(Node<T>* otherNode) {
    if (otherNode == nullptr) return nullptr;
    auto newNode = new Node<T>(otherNode->value);
    newNode->setLeft(_deepCopy(otherNode->left()));
    newNode->setRight(_deepCopy(otherNode->right()));
    return newNode;
}

template<typename T>
BSTree<T>::~BSTree() {
    _deconstruct(_root);
}

template<typename T>
void BSTree<T>::_deconstruct(Node<T>* root) {
    if (root == nullptr) return;
    // Deallocate children and then parent node (Post Order)
    _deconstruct(root->left());
    _deconstruct(root->right());
    delete root;
}

template<typename T>
BSTree<T>::BSTree(bool allowDuplicates): _root(nullptr), _size(0), _allowDuplicates(allowDuplicates) {}

template<typename T>
Node<T>* BSTree<T>::_inOrder(Node<T>* root) const {
    if (root == nullptr) return nullptr;

}

// Visit prints
template<typename T>
void BSTree<T>::_inOrderVisit(Node<T>* root) const {
    if (root == nullptr) return;
    _inOrderVisit(root->left());
    std::cout << root << std::setw(4);
    _inOrderVisit(root->right());
}
template<typename T>
void BSTree<T>::_reverseInOrderVisit(Node<T>* root) const {
    if (root == nullptr) return;
    _inOrderVisit(root->right());
    std::cout << root << std::setw(4);
    _inOrderVisit(root->left());
}
template<typename T>
void BSTree<T>::_preOrderVisit(Node<T>* root) const {
    if (root == nullptr) return;
    std::cout << root << std::setw(4);
    _inOrderVisit(root->left());
    _inOrderVisit(root->right());
}
template<typename T>
void BSTree<T>::_postOrderVisit(Node<T>* root) const {
    if (root == nullptr) return;
    _inOrderVisit(root->left());
    _inOrderVisit(root->right());
    std::cout << root << std::setw(4);
}

template<typename T>
void BSTree<T>::inOrderVisit() const {
    _inOrderVisit(_root);
}

template<typename T>
void BSTree<T>::reverseInOrderVisit() const {
    _reverseInOrderVisit(_root);
}
template<typename T>
void BSTree<T>::preOrderVisit() const {
    _preOrderVisit(_root);
}
template<typename T>
void BSTree<T>::postOrderVisit() const {
    _postOrderVisit(_root);
}


// Tree Operations
template<typename T>
void BSTree<T>::insert(T value) {
    if (!_size) {
        _root = new Node(value);
        // _height = 1;
    } else {
        // size_t height = 1;
        Node<T> *node = _root;
        Node<T> *next = _root;
        while (next != nullptr) {
            node = next;
            if (!_allowDuplicates && value == node->value)
                return;  // Early exit without done nothing if value is already present and duplicates aren't allower
            if (value < node->value) {
                next = node->left();
            } else {
                next = node->right();
            }
            // height++;
        }
        if (value < node->value) {
            node->setLeft(new Node(value));
        } else {
            node->setRight(new Node(value));
        }
        // if (height > _height) _height = height;
    }
    _size++;
}


template <typename T>
Node<T>* BSTree<T>::_findNode(const T& value, Node<T>* root) const {
    if (root == nullptr) return nullptr;
    if (value == root->value) return root;
    if (value < root->value) return _findNode(value, root->left());
    return _findNode(value, root->right());
}
template <typename T>
Node<T>* BSTree<T>::_findMinNode(Node<T> *next, Node<T> *root) const {
    if (next == nullptr) return root;
    return _findMinNode(root->left(), next);
}
template <typename T>
Node<T>* BSTree<T>::_findMaxNode(Node<T> *next, Node<T> *root) const {
    if (next == nullptr) return root;
    return _findMaxNode(root->right(), next);
}


template <typename T>
Node<T>* BSTree<T>::_remove(const T& value, Node<T>* root, bool& removed) {
    if (root == nullptr) {
        removed = false;
        return nullptr;
    }
    if (value < root->value) root->setLeft(_remove(value, root->left(), removed));
    else if (value > root->value) root->setRight(_remove(value, root->right(), removed));
    else {
        removed = true;
        if (root->right() == nullptr && root->left() == nullptr) {
            // Case 1: Node to remove has NO children
            delete root;
            return nullptr;
        } else if (root->left() == nullptr) {
            // Case 2.1 : Node has only one child (right)
            Node<T> *temp = root->right();
            delete root;
            return temp;
        } else if (root->right() == nullptr) {
            // Case 2.2 : Node has only one child (left)
            Node<T> *temp = root->left();
            delete root;
            return temp;
        } else {
            // Case 3: Node has two children
            Node<T> *minNode = _findMinNode(root->right(), root->right());
            root->value = minNode->value;
            _remove(minNode->value,
                    root->right(), removed);  // Remove the node of the minimum value, as it's now contained in the actual root node
        }
    }
    return root;
}
template <typename T>
bool BSTree<T>::remove(T value) {
    bool removed = false;
    _remove(value, _root, removed);
    if (removed) _size--;
    return removed;
}

template<typename T>
bool BSTree<T>::allowDuplicates() const { return _allowDuplicates; }
template<typename T>
size_t BSTree<T>::size() const { return _size; }
template<typename T>
bool BSTree<T>::isEmpty() const { return _size == 0; }
template<typename T>
size_t BSTree<T>::_height(Node<T>* root) const {
    if (root == nullptr) {
        return 0; // Empty Tree -> Height = 0
    }
    int leftHeight = _height(root->left());
    int rightHeight = _height(root->right());
    return 1 + std::max(leftHeight, rightHeight);
}

template<typename T>
bool BSTree<T>::search(T value) {
    return _findNode(value, _root) != nullptr;
}

template<typename T>
T BSTree<T>::minValue() const {
    if (_size == 0) throw EmptyTreeException();
    return _findMinNode(_root, _root)->value;
}

template<typename T>
T BSTree<T>::maxValue() const {
    if (_size == 0) throw EmptyTreeException();
    return _findMaxNode(_root, _root)->value;
}

template<typename T>
size_t BSTree<T>::height() const { return _height(_root); }


template<typename F>
std::ostream& operator<<(std::ostream& os, const BSTree<F>& tree) {
    return os;
}

#endif //MY_DATA_STRUCTURES_BSTREE_TPP
