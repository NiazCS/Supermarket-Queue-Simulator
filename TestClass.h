//niaz hussain
//cst 202 data structures
//testclass.h

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "Queue.h"

//define test functions for queue and shopper
class TestClass {
public:
    static void testEnqueueEmpty();
    static void testEnqueueOneNode();
    static void testDequeueSingleNode();
    static void testDequeueTwoNodes();
    static void testSimulation12Hours();
};

#endif
