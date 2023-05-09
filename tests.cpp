/*
Author: BRANDON KIM
DATE: 4/11/2023
Course: CS 251

Description: This file(tests.cpp) is used for testing

*/



/// @file tests.cpp
/// @date March 17, 2023

/// 
/// TODO

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

// TODO:
// Choose which framework to keep and delete the other.
//



using namespace std;
// Google Test Framework Testing
#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <map>
#include <set>
#include <vector>
#include <string>

//Tests for priorityqueue.h --------------------------------
//Tests for enqueue function
//Tests for size function and default constructor
TEST(PQTEST, sizeConstructorFunction) {
    priorityqueue<int> pq;

    EXPECT_EQ(0,pq.Size());
    pq.enqueue(100,4);
    EXPECT_EQ(1,pq.Size());
    pq.enqueue(200,5);
    EXPECT_EQ(2,pq.Size());
    pq.enqueue(300,4);
    EXPECT_EQ(3,pq.Size());
}
//string test for size, pq
TEST(PQTEST, sizeConstructorFunction1) {
    priorityqueue<string> pq;

    EXPECT_EQ(0,pq.Size());
    pq.enqueue("one",4);
    EXPECT_EQ(1,pq.Size());
    pq.enqueue("two",5);
    EXPECT_EQ(2,pq.Size());
    pq.enqueue("three",4);
    EXPECT_EQ(3,pq.Size());
}
//Another test for size
TEST(PQTEST, sizeConstructorFunction2) {
    priorityqueue<int> pq;
    priorityqueue<int> pq1;
    EXPECT_EQ(pq,pq1);
    
}
//Test for ToString() 
//Citation : Professor Adam Koehler, project description example
TEST(PQTEST,toStringTest) {
   
    // EXPECT_EQ(pq.toString(),"");

    map<int, vector<int> > map;
int n = 9;
int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
priorityqueue<int> pq;
for (int i = 0; i < n; i++) {
    pq.enqueue(vals[i], prs[i]);
    map[prs[i]].push_back(vals[i]);
}
EXPECT_EQ(pq.Size(), 9);
stringstream ss;
for (auto e: map) {
    int priority = e.first;
    vector <int> values = e.second;
    for (size_t j = 0; j < values.size(); j++){
        ss << priority << " value: " << values[j] << endl;
    }
}
EXPECT_EQ(pq.toString(), ss.str());
}

//Test for clear() function
TEST(PQTEST,clearTest) {
    priorityqueue<int> pq;
    pq.enqueue(1,1);
    pq.clear();
    EXPECT_EQ(pq.Size(),0);
    //Size is correct

}
//Test for operator= function
TEST(PQTEST,assignmentOpTest) {
    priorityqueue<int> pq;
    priorityqueue<int> pq1;
    pq.enqueue(1,1);
    pq1 = pq;
    EXPECT_EQ(1,pq1.Size());
    priorityqueue<int> pq2;
    pq1 = pq2;
    EXPECT_EQ(0,pq1.Size());

    pq1.enqueue(2,2);
    pq1.clear();
    EXPECT_EQ(1,pq.Size());
}
//Testing duplicates for operator= function
TEST(PQTEST,assignmentOpTest2) {
    priorityqueue<int> pq;
    priorityqueue<int> pq1;
    pq.enqueue(1,1);
    pq.enqueue(2,2);
    pq.enqueue(3,3);
    pq.enqueue(4,2);
    pq1 = pq;
    EXPECT_EQ(4,pq1.Size());
}
//Testing begin() and next()
// string output = testing::internal::GetCapturedStdout();
//  EXPECT_EQ(output,"It's a Shape at x: 2, y: 6\n");

TEST(PQTEST, BEGINNEXTTEST) {
    //test without duplicates
    priorityqueue<int> pq;
    pq.enqueue(3,3);
    pq.enqueue(1,1);
    pq.enqueue(2,2);

    pq.begin();
    int value;
    int priority;
    pq.next(value,priority);
    EXPECT_EQ(value,1);
    EXPECT_EQ(priority,1);
    priorityqueue<int> pq1;
    pq1.enqueue(3,3);
    pq1.enqueue(1,1);
    pq1.enqueue(2,2);

    pq1.enqueue(4,1);
    pq1.begin();
    pq1.next(value,priority);
    pq1.next(value,priority);
    EXPECT_EQ(value,4);
    EXPECT_EQ(priority,1);
}
//Testing Dequeue() function
TEST(PQTEST, DEQUEUETEST) {
    //Testing fully left tree, including root
    priorityqueue<int> pq;
    pq.enqueue(7,7);
    pq.enqueue(6,6);
    pq.enqueue(5,5);
    pq.enqueue(4,4);
    int value = pq.dequeue();
    EXPECT_EQ(4,value);
    value = pq.dequeue();
    EXPECT_EQ(5,value);
    value = pq.dequeue();
    EXPECT_EQ(6,value);
    value = pq.dequeue();
    EXPECT_EQ(7,value);
    
    //Testing normal tree no dups
    pq.enqueue(6,6);
    pq.enqueue(7,7);
    pq.enqueue(5,5);
    value = pq.dequeue();
    EXPECT_EQ(5,value);
    value = pq.dequeue();
    EXPECT_EQ(6,value);
    value = pq.dequeue();
    EXPECT_EQ(7,value);
    //Testing with dups normal tree
    pq.enqueue(6,6);
    pq.enqueue(7,7);
    pq.enqueue(5,5);
    pq.enqueue(10,5);
    value = pq.dequeue();
    EXPECT_EQ(5,value);
    value = pq.dequeue();
    EXPECT_EQ(10,value);
    value = pq.dequeue();
    EXPECT_EQ(6,value);
    value = pq.dequeue();
    EXPECT_EQ(7,value);

}
//Testing peek() function
TEST(PQTEST, PEEKTEST) {
    priorityqueue<int> pq;
    pq.enqueue(7,7);
    pq.enqueue(6,6);
    int value = pq.peek();
    EXPECT_EQ(pq.Size(),2);
    EXPECT_EQ(6,value);
    value = pq.peek();
    EXPECT_EQ(pq.Size(),2);
    EXPECT_EQ(6,value);
}
//Testing equality operator
TEST(PQTEST, EQUALITYOPERATORTEST) {
    priorityqueue<int> pq;
    pq.enqueue(5,5);
    pq.enqueue(3,3);
    pq.enqueue(3,2);
    priorityqueue<int> pq1;
    pq1.enqueue(5,5);
    pq1.enqueue(3,3);
    pq1.enqueue(3,2);
    EXPECT_EQ(pq==pq1,true);
    pq.enqueue(7,5);
    pq1.enqueue(7,5);
    EXPECT_EQ(pq==pq1,true);
    pq.enqueue(8,5);
    EXPECT_EQ(pq==pq1,false);
}



