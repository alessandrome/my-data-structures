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

TEST(AVLTreeTest, EmptyTreeAllowDuplicates) {
    myds::AVLTree<int> t1(true);
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), true);
}

TEST(AVLTreeTest, AddNode) {
    myds::AVLTree<int> t1;
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), false);
    t1.insert(5);
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1.height(), 1);
    t1.insert(10);
    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(2);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(2);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t1.height(), 2);
}

TEST(AVLTreeTest, AddDuplicates) {
    myds::AVLTree<int> t1{true};
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), true);
    t1.insert(5);
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1.height(), 1);
    t1.insert(10);
    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(2);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(2);
    EXPECT_EQ(t1.size(), 4);
    EXPECT_EQ(t1.height(), 3);
}

TEST(AVLTreeTest, BalancingRight) {
    myds::AVLTree<int> t1;
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), false);
    t1.insert(5);
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1.height(), 1);
    t1.insert(10);
    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(20);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(40);
    EXPECT_EQ(t1.size(), 4);
    EXPECT_EQ(t1.height(), 3);
    t1.insert(50);
    EXPECT_EQ(t1.size(), 5);
    EXPECT_EQ(t1.height(), 3);
}

TEST(AVLTreeTest, BalancingLeft) {
    myds::AVLTree<int> t1;
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), false);
    t1.insert(50);
    EXPECT_EQ(t1.size(), 1);
    EXPECT_EQ(t1.height(), 1);
    t1.insert(40);
    EXPECT_EQ(t1.size(), 2);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(20);
    EXPECT_EQ(t1.size(), 3);
    EXPECT_EQ(t1.height(), 2);
    t1.insert(10);
    EXPECT_EQ(t1.size(), 4);
    EXPECT_EQ(t1.height(), 3);
    t1.insert(5);
    EXPECT_EQ(t1.size(), 5);
    EXPECT_EQ(t1.height(), 3);
}

TEST(AVLTreeTest, Find) {
    myds::AVLTree<int> t1 = createTestBSTree();
    EXPECT_EQ(t1.search(50), true);
    EXPECT_EQ(t1.search(10), true);
    EXPECT_EQ(t1.search(12), true);
    EXPECT_EQ(t1.search(13), false);
    EXPECT_EQ(t1.search(77), false);
}

TEST(AVLTreeTest, Remove) {
    myds::AVLTree<int> t1 = createTestBSTree();
    size_t startSize = t1.size();
    EXPECT_EQ(t1.remove(50), true);
    EXPECT_EQ(t1.size(), startSize - 1);
    EXPECT_EQ(t1.remove(50), false);
    EXPECT_EQ(t1.size(), startSize - 1);
    EXPECT_EQ(t1.remove(10), true);
    EXPECT_EQ(t1.size(), startSize - 2);
    EXPECT_EQ(t1.remove(12), true);
    EXPECT_EQ(t1.size(), startSize - 3);
    EXPECT_EQ(t1.remove(13), false);
    EXPECT_EQ(t1.size(), startSize - 3);
    EXPECT_EQ(t1.remove(77), false);
    EXPECT_EQ(t1.size(), startSize - 3);
}

TEST(AVLTreeTest, MinValue) {
    myds::AVLTree<int> t1 = createTestBSTree();
    EXPECT_EQ(t1.minValue(), 10);
    t1.remove(10);
    EXPECT_EQ(t1.minValue(), 12);
}

TEST(AVLTreeTest, MaxValue) {
    myds::AVLTree<int> t1 = createTestBSTree();
    EXPECT_EQ(t1.maxValue(), 90);
    t1.remove(90);
    EXPECT_EQ(t1.maxValue(), 80);
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
