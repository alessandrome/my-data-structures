#include <iostream>
#include <iomanip>
#include <sstream>
#include <gtest/gtest.h>
#include "../templated/Linear/Vector.h"

using namespace std;
using myds::Vector;

Vector<int> createVector() {
    Vector<int> rVec;
    for (int i = 0; i < myds::DEFAULT_VECTOR_CAPACITY - 1; i++)
        rVec.append(i);
    return rVec;
}

const std::string EXPECTED_STR = "[0, 1, 2, 3, 4, 5, 6]";
const std::string EXPECTED_STR_2 = "[0, 1, 2, 3, 4, 5, 6, 100, 101]";
const std::string EXPECTED_STR_3 = "[0, 1, 2, 3, 4, 5, 6, 7, 8, 100, 101]";

TEST(VectorTest, DefaultVector) {
    Vector<int> emptyVec;
    ASSERT_EQ(emptyVec.length(), 0);
    ASSERT_EQ(emptyVec.capacity(), myds::DEFAULT_VECTOR_CAPACITY);
}

TEST(VectorTest, VectorWithCapacity) {
    Vector<int> emptyVec(2);
    ASSERT_EQ(emptyVec.length(), 0);
    ASSERT_EQ(emptyVec.capacity(),2);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> v1 = createVector();
    Vector<int> v2 = v1;
    for (size_t i = 0; i < v1.length(); i++) {
        ASSERT_EQ(v1.get(i), v2.get(i));
    }
}

TEST(VectorTest, ZeroCapacity) {
    Vector<int> emptyVec(0);
    ASSERT_EQ(emptyVec.length(), 0);
    ASSERT_EQ(emptyVec.capacity(), 0);
    emptyVec.prepend(1);
    ASSERT_EQ(emptyVec.length(), 1);
    ASSERT_EQ(emptyVec.capacity(), myds::DEFAULT_VECTOR_CAPACITY);
}

TEST(VectorTest, EmptyMethod) {
    Vector<int> v1;
    ASSERT_EQ(v1.empty(), true);
    v1.append(5);
    ASSERT_EQ(v1.empty(), false);
}

TEST(VectorTest, FullMethod) {
    Vector<int> v1 = createVector();
    ASSERT_EQ(v1.full(), false);
    v1.append(5);
    ASSERT_EQ(v1.full(), true);
}

TEST(VectorTest, Append) {
    Vector<int> v1 = createVector();
    // TODO
}

TEST(VectorTest, Prepend) {
    Vector<int> v1 = createVector();
    // TODO
}

TEST(VectorTest, Remove) {
    Vector<int> v1 = createVector();
    // TODO
}

TEST(VectorTest, Get) {
    Vector<int> v1 = createVector();
    // TODO
}

TEST(VectorTest, Set) {
    Vector<int> v1 = createVector();
    // TODO
}

TEST(VectorTest, Find) {
    Vector<int> v1 = createVector();
    std::optional<size_t> found = v1.find(5), notFound = v1.find(100);
    ASSERT_EQ(found.has_value(), true);
    ASSERT_EQ(notFound.has_value(), false);
    ASSERT_EQ(found.value(), 5);
}

TEST(VectorTest, IncreaseCapacity) {
    Vector<int> v1 = createVector();
    size_t capacity = v1.capacity();
    v1.append(100);
    ASSERT_EQ(v1.capacity(), capacity);
    v1.append(101);
    ASSERT_EQ(v1.capacity(), capacity * 2);
}

TEST(VectorTest, PlusEqualValueOperator) {
    Vector<int> v1 = createVector();
    size_t capacity = v1.capacity();
    v1 += 100;
    ASSERT_EQ(v1.capacity(), capacity);
    v1 += 101;
    ASSERT_EQ(v1.capacity(), capacity * 2);
    std::stringstream ss;
    ss << v1;
    ASSERT_EQ(ss.str(), EXPECTED_STR_2);
}

TEST(VectorTest, PlusEqualVectorOperatorWithResize) {
    Vector<int> v1 = createVector();
    Vector<int> v2;
    v2.append(100);
    v2.append(101);
    size_t capacity = v1.capacity();
    v1 += v2;
    ASSERT_EQ(v1.capacity(), capacity + v2.capacity());
    std::stringstream ss;
    ss << v1;
    ASSERT_EQ(ss.str(), EXPECTED_STR_2);
}

TEST(VectorTest, PlusEqualVectorOperatorWithoutResize) {
    Vector<int> v1 = createVector();
    Vector<int> v2(3);
    v2.append(100);
    v2.append(101);
    v1.append(7);
    v1.append(8);
    size_t capacity = v1.capacity();
    v1 += v2;
    ASSERT_EQ(v1.capacity(), capacity);
    std::stringstream ss;
    ss << v1;
    ASSERT_EQ(ss.str(), EXPECTED_STR_3);
}

TEST(VectorTest, Assignment) {
    Vector<int> v1 = createVector();
    Vector<int> v2;
    v2.append(100);
    v2 = v1;
    for (size_t i = 0; i < v1.length(); i++) {
        ASSERT_EQ(v1.get(i), v2.get(i));
    }
}

TEST(VectorTest, SquareBracket) {
    Vector<int> v1 = createVector();
    auto element = v1.get(0);
    ASSERT_EQ(v1[0], element);
    ASSERT_EQ(v1[0], 0);
    ASSERT_EQ(v1[3], v1.get(3));
    ASSERT_EQ(v1[3], 3);
}

TEST(VectorTest, Stream) {
    Vector<int> v1 = createVector();
    std::stringstream ss;
    ss << v1;
    ASSERT_EQ(ss.str(), EXPECTED_STR);
}
