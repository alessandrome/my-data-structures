#include <iostream>
#include <iomanip>
#include "../templated/Linear/Queue.h"

using namespace std;

// From root folder
// g++ ./tests/stack_tests.cpp ./templated/Stack.cpp -o stack_tests -g2
int main() {
    double topVal = 0;
    Queue<int> myQueue{};
    try {
        cout << "Trying top() new empty stack: ";
        myQueue.front();
        cout << "[ERR] No exception!";
    } catch (QueueEmptyException& e) {
        cout << "[OK] \"" << e.what() << "\"" << endl;
    }
    try {
        cout << "Trying pop() new empty stack: ";
        myQueue.back();
        cout << "[ERR] No exception!";
    } catch (QueueEmptyException& e) {
        cout << "[OK] \"" << e.what() << "\"" << endl;
    }

    myQueue.push(3);
    myQueue.push(4);
    myQueue.push(5);
    myQueue.push(8);
    topVal = myQueue.size();
    if (myQueue.size() == 4){
        cout << "[OK] " << "size(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "size(): " << topVal << endl;
    }

    topVal = myQueue.front();
    if (topVal == 3) {
        cout << "[OK] " << "First front(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "First front(): " << topVal << endl;
    }
    topVal = myQueue.back();
    if (topVal == 8) {
        cout << "[OK] " << "First back(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "First back(): " << topVal << endl;
    }

    topVal = myQueue.front();
    if (topVal == 3) {
        cout << "[OK] " << "Second front(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "Second front(): " << topVal << endl;
    }
    topVal = myQueue.back();
    if (topVal == 8) {
        cout << "[OK] " << "Second back(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "Second back(): " << topVal << endl;
    }

    topVal = myQueue.pop();
    if (topVal == 3) {
        cout << "[OK] " << "First pop(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "First pop(): " << topVal << endl;
    }
    topVal = myQueue.back();
    if (topVal == 8) {
        cout << "[OK] " << "Third back(): " << topVal << endl;
    }  else {
        cout << "[ERR] " << "Third back(): " << topVal << endl;
    }

    // Emptiness
    if (!myQueue.empty()) {
        cout << "[OK] " << "Not empty: " << myQueue.size() << " elements" << endl;
    }  else {
        cout << "[ERR] " << "Not Empty but considered empty " << topVal << endl;
    }

    // Operator Overloads
    myQueue += 100;
    if (myQueue.back() == 100) {
        cout << "[OK] " << "Correct += (push) overload" << endl;
    }  else {
        cout << "[ERR] " << "Expected pushed 100 with += operator, " << myQueue.back() << " found instead" << endl;
    }
    return 0;
}
