#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <gtest/gtest.h>
#include "../templated/NonLinear/AVLTree/AVLTree.h"

using namespace std;

myds::AVLTree<int> createTestBSTree() {
    myds::AVLTree<int> tree;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 90, 25, 15, 10, 12};
    for (int value : values) {
        tree.insert(value);
    }
    return tree;
}

TEST(AVLTreeTest, EmptyTree) {
    myds::AVLTree<int> t1;
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), false);
}

bool test_new_tree() {
    try {
        myds::AVLTree<int> t1{};
        myds::AVLTree<int> t2{true};
        assert(t1.size() == 0);
        assert(t1.height() == 0);
        assert(t1.allowDuplicates() == false);
        assert(t2.size() == 0);
        assert(t2.height() == 0);
        assert(t2.allowDuplicates() == true);
    } catch (...) {
        return false;
    }
    return true;
}

bool test_add() {
    try {
        myds::AVLTree<int> t1{};
        assert(t1.size() == 0);
        assert(t1.height() == 0);
        assert(t1.allowDuplicates() == false);
        t1.insert(5);
        assert(t1.size() == 1);
        assert(t1.height() == 1);
        t1.insert(10);
        assert(t1.size() == 2);
        assert(t1.height() == 2);
        t1.insert(2);
        assert(t1.size() == 3);
        assert(t1.height() == 2);
        // No duplicates
        t1.insert(2);
        assert(t1.size() == 3);
        assert(t1.height() == 2);
        myds::AVLTree<int> t2{true};
        assert(t2.size() == 0);
        assert(t2.height() == 0);
        assert(t2.allowDuplicates() == true);
        t2.insert(5);
        assert(t2.size() == 1);
        assert(t2.height() == 1);
        t2.insert(10);
        assert(t2.size() == 2);
        assert(t2.height() == 2);
        t2.insert(2);
        assert(t2.size() == 3);
        assert(t2.height() == 2);
        t2.insert(2);
        assert(t2.size() == 4);
        assert(t2.height() == 3);
    } catch (...) {
        return false;
    }
    return true;
}

bool test_find() {
    try {
        myds::AVLTree<int> t1 = createTestBSTree();
        assert(t1.search(50));
        assert(t1.search(10));
        assert(t1.search(12));
        assert(!t1.search(13));
        assert(!t1.search(77));
    } catch (...) {
        return false;
    }
    return true;
}

bool test_remove() {
    try {
        myds::AVLTree<int> t1 = createTestBSTree();
        assert(t1.remove(50));
        assert(!t1.remove(50));
        assert(t1.remove(10));
        assert(t1.remove(12));
        assert(!t1.remove(13));
        assert(!t1.remove(77));
    } catch (...) {
        return false;
    }
    return true;
}

bool test_min() {
    try {
        myds::AVLTree<int> t1 = createTestBSTree();
        assert(t1.minValue() == 10);
        t1.remove(10);
        assert(t1.minValue() == 12);
    } catch (...) {
        return false;
    }
    return true;
}

bool test_max() {
    try {
        myds::AVLTree<int> t1 = createTestBSTree();
        assert(t1.maxValue() == 90);
        t1.remove(90);
        assert(t1.minValue() == 80);
    } catch (...) {
        return false;
    }
    return true;
}

// From root folder
//int main() {
//    int total = 0, passed = 0;
//    bool test = test_new_tree();
//    total++; passed += test;
//    cout << "[" << (test ? "OK" : "ERR") << "] test_new_tree()" << endl;
//
//    test = test_add();
//    total++; passed += test;
//    cout << "[" << (test ? "OK" : "ERR") << "] test_add()" << endl;
//
//    test = test_find();
//    total++; passed += test;
//    cout << "[" << (test ? "OK" : "ERR") << "] test_find()" << endl;
//
//    test = test_remove();
//    total++; passed += test;
//    cout << "[" << (test ? "OK" : "ERR") << "] test_remove()" << endl;
//
//    cout << "[" << passed << "/" << total << "] Passed/Total" << endl;
//    return 0;
//}
