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

TEST(VectorTest, Stream) {
    Vector<int> v1 = createVector();
    std::stringstream ss;
    ss << v1;
    ASSERT_EQ(ss.str(), EXPECTED_STR);
}
