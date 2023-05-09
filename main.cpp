
using namespace std;
// Google Test Framework Testing
#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <map>
#include <set>
#include <vector>



int main() {

    priorityqueue<int> pq;
    pq.enqueue(5,5);
    pq.enqueue(7,5);
    pq.enqueue(3,3);
    pq.enqueue(3,2);
    priorityqueue<int> pq1;
    pq1.enqueue(5,5);
    pq1.enqueue(7,5);
    pq1.enqueue(3,3);
    pq1.enqueue(3,2);
    cout << pq.toString();
    cout << "---------------------" << endl;
    cout << pq1.toString();
    cout << "---------------------" << endl;
    if(pq == pq1) {
      cout << "Comparing: ";
      cout << "True" << endl;
    } else {
      cout << "Comparing: ";
      cout << "False" << endl;
    }
    pq.clear();
    pq1.clear();
    // pq.printRoot1();
    // pq1.printRoot1();
    cout << "Sizes before: " << pq.Size() << endl;
    cout << "Sizes before: " << pq1.Size() << endl;
    cout << "End" << endl;
    return 0;
}