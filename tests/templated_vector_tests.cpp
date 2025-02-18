#include <iostream>
#include <iomanip>
#include <gtest/gtest.h>
#include "../templated/Linear/Vector.h"

using namespace std;
using myds::Vector;

TEST(Vector, DefaultVector) {
    Vector<int> emptyVec;
    ASSERT_EQ(emptyVec.length(), 0);
    ASSERT_EQ(emptyVec.capacity(), myds::DEFAULT_VECTOR_CAPACITY);
}

// From root folder
int main() {
    double topVal = 0;
    List<int> list{};
    std::cout << std::fixed << std::setprecision(3);
    list.append(1);
    cout << "Length: " << list.length() << " - " << list << endl;  // [1, 2]
    list.append(2);
    cout << "Length: " << list.length() << " - " << list << endl;  // [1, 2]
    list.prepend(3);
    cout << "Length: " << list.length() << " - " << list << endl;  // [3, 1, 2]
    list.insert(4, 1);
    cout << "Length: " << list.length() << " - " << list << endl;  // [3, 4, 1, 2]
    list.insert(6, 2);
    cout << "Length: " << list.length() << " - " << list << endl;  // [3, 4, 6, 1, 2]
    list.set(5, 2);
    cout << "Length: " << list.length() << " - " << list << endl;  // [3, 4, 5, 1, 2]
    cout << "Get(3): " << list.get(3) << endl;  // 1
    list.remove(1);
    cout << "Length: " << list.length() << " - " << list << endl;  // [3, 5, 1, 2]
    list.remove(3);
    cout << "Length: " << list.length() << " - " << list << endl;  // [3, 5, 1]
    cout << "Empty(): " << (list.empty() ? "true" : "false") << endl;  // False
    cout << "Overload [] (using 1): " << list[1] << endl;
    list[1] = 7;
    cout << "Overload [] (using 1 after direct edit): " << list[1] << endl;
    cout << list << endl;
    return 0;
}
