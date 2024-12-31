#include <iostream>
#include <iomanip>
#include "../templated/List.h"

using namespace std;

// From root folder
// g++ ./tests/stack_tests.cpp ./templated/Stack.cpp -o stack_tests -g2
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
    return 0;
}
