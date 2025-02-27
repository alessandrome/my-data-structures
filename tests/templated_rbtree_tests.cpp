#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <gtest/gtest.h>
#include "../templated/NonLinear/RedBlackTree/RedBlackTree.h"

using namespace std;
using myds::RedBlackTree;

RedBlackTree<int> createTestBSTree() {
    myds::RedBlackTree<int> tree;
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80, 90, 25, 15, 10, 12};
    for (int value : values) {
        tree.insert(value);
    }
    return tree;
}

TEST(RedBlackTreeTest, EmptyTree) {
    myds::RedBlackTree<int> t1;
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), false);
}

TEST(RedBlackTreeTest, EmptyTreeAllowDuplicates) {
    myds::RedBlackTree<int> t1(true);
    EXPECT_EQ(t1.size(), 0);
    EXPECT_EQ(t1.height(), 0);
    EXPECT_EQ(t1.allowDuplicates(), true);
}

TEST(RedBlackTreeTest, AddNode) {
    myds::RedBlackTree<int> t1;
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

TEST(RedBlackTreeTest, AddDuplicates) {
    myds::RedBlackTree<int> t1{true};
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

TEST(RedBlackTreeTest, BalancingRight) {
    myds::RedBlackTree<int> t1;
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

TEST(RedBlackTreeTest, BalancingLeft) {
    myds::RedBlackTree<int> t1;
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

TEST(RedBlackTreeTest, Find) {
    myds::RedBlackTree<int> t1 = createTestBSTree();
    EXPECT_EQ(t1.search(50), true);
    EXPECT_EQ(t1.search(10), true);
    EXPECT_EQ(t1.search(12), true);
    EXPECT_EQ(t1.search(13), false);
    EXPECT_EQ(t1.search(77), false);
}

TEST(RedBlackTreeTest, Remove) {
    myds::RedBlackTree<int> t1 = createTestBSTree();
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

TEST(RedBlackTreeTest, MinValue) {
    myds::RedBlackTree<int> t1 = createTestBSTree();
    EXPECT_EQ(t1.minValue(), 10);
    t1.remove(10);
    EXPECT_EQ(t1.minValue(), 12);
}

TEST(RedBlackTreeTest, MaxValue) {
    myds::RedBlackTree<int> t1 = createTestBSTree();
    EXPECT_EQ(t1.maxValue(), 90);
    t1.remove(90);
    EXPECT_EQ(t1.maxValue(), 80);
}
