#include <iostream>
#include "../Stack.h"

using namespace std;

// g++ ./tests/stack_tests.cpp Stack.cpp -o stack_tests -g2
int main() {
    int topVal = 0;
    Stack myStack = Stack{};
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

    myStack.push(3);
    myStack.push(4);
    topVal = myStack.size();
    if (myStack.size() == 2){
        cout << "[OK] " << "size(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "size(): " << topVal << endl;
    }

    topVal = myStack.top();
    if (topVal == 4) {
        cout << "[OK] " << "First pop(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "First pop(): " << topVal << endl;
    }
    myStack.pop();
    topVal = myStack.top();
    if (topVal == 3) {
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
    return 0;
}
