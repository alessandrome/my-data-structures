#include <iostream>
#include <iomanip>
#include "../templated/Linear/Stack.h"

using namespace std;

// From root folder
// g++ ./tests/stack_tests.cpp ./templated/Stack.cpp -o stack_tests -g2
int main() {
    double topVal = 0;
    Stack<double> myStack = Stack<double>{};
    std::cout << std::fixed << std::setprecision(3);
    try {
        cout << "Trying top() new empty stack: ";
        myStack.top();
        cout << "[ERR] No exception!";
    } catch (StackEmptyException& e) {
        cout << "[OK] \"" << e.what() << "\"" << endl;
    }
    try {
        cout << "Trying pop() new empty stack: ";
        myStack.top();
        cout << "[ERR] No exception!";
    } catch (StackEmptyException& e) {
        cout << "[OK] \"" << e.what() << "\"" << endl;
    }

    myStack.push(3.1);
    myStack.push(4.106);
    topVal = myStack.size();
    if (myStack.size() == 2){
        cout << "[OK] " << "size(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "size(): " << topVal << endl;
    }

    topVal = myStack.top();
    if (topVal == 4.106) {
        cout << "[OK] " << "First pop(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "First pop(): " << topVal << endl;
    }
    myStack.pop();
    topVal = myStack.top();
    if (topVal == 3.1) {
        cout << "[OK] " << "Second pop(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "Second pop(): " << topVal << endl;
    }

    // Emptiness
    if (!myStack.empty()) {
        cout << "[OK] " << "Not empty: " << myStack.size() << " elements" << endl;
    }  else {
        cout << "[ERR] " << "Not Empty but considered empty " << topVal << endl;
    }
    myStack.pop();
    if (myStack.empty()) {
        cout << "[OK] " << "Empty" << endl;
    }  else {
        cout << "[ERR] " << "Empty but considered not empty" << endl;
    }

    myStack += 5;
    if (myStack.top() == 5) {
        cout << "[OK] " << "Correctly used +=" << endl;
    }  else {
        cout << "[ERR] " << "Error with +=" << endl;
    }
    return 0;
}
