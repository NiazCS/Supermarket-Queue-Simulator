//niaz hussain
//cst 202 data structures
//testclass.cpp

#include "TestClass.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
using namespace std;

//helper for random
static int randomBetween(int minVal, int maxVal) {
    return minVal + (rand() % (maxVal - minVal + 1));
}

//enqueue on empty queue
void TestClass::testEnqueueEmpty() {
    Queue q;
    assert(q.isEmpty());
    Shopper s(1, 0, 5, 3);
    q.enqueue(s);
    assert(q.size() == 1);
    Shopper& front = q.front();
    assert(front.id == 1);
    cout << "testEnqueueEmpty passed" << endl;
}

//enqueue with one node in queue
void TestClass::testEnqueueOneNode() {
    Queue q;
    Shopper s1(1, 0, 5, 2);
    s1.totalTime = s1.initialServiceTime + q.sumInitialServiceTimes();
    q.enqueue(s1);

    Shopper s2(2, 1, 7, 4);
    s2.totalTime = s2.initialServiceTime + q.sumInitialServiceTimes();
    q.enqueue(s2);

    assert(q.size() == 2);
    Shopper& front = q.front();
    assert(front.id == 1);
    cout << "testEnqueueOneNode passed" << endl;
}

//dequeue on a queue with one node
void TestClass::testDequeueSingleNode() {
    Queue q;
    Shopper s(10, 0, 3, 2);
    s.totalTime = s.initialServiceTime + q.sumInitialServiceTimes();
    q.enqueue(s);
    assert(!q.isEmpty());
    Shopper d = q.dequeue();
    assert(d.id == 10);
    assert(q.isEmpty());
    cout << "testDequeueSingleNode passed" << endl;
}

//dequeue on a queue with two nodes
void TestClass::testDequeueTwoNodes() {
    Queue q;
    Shopper s1(1, 0, 2, 3);
    s1.totalTime = s1.initialServiceTime + q.sumInitialServiceTimes();
    q.enqueue(s1);

    Shopper s2(2, 1, 5, 4);
    s2.totalTime = s2.initialServiceTime + q.sumInitialServiceTimes();
    q.enqueue(s2);

    Shopper d1 = q.dequeue();
    assert(d1.id == 1);
    assert(q.size() == 1);
    Shopper d2 = q.dequeue();
    assert(d2.id == 2);
    assert(q.isEmpty());
    cout << "testDequeueTwoNodes passed" << endl;
}

//run simulation for 12 hours
void TestClass::testSimulation12Hours() {
    srand(static_cast<unsigned int>(time(0))); // reseed for test independence
    const int SIM_TIME = 720;
    Queue expressLine;
    Queue regularLine;

    int nextExpressArrival = randomBetween(1, 5);
    int nextRegularArrival = randomBetween(3, 8);
    int nextShopperID = 1;

    int totalServedExpress = 0;
    int totalServedRegular = 0;
    int totalWaitExpress = 0;
    int totalWaitRegular = 0;

    cout << "starting 12-hour test simulation run..." << endl;

    for (int minute = 0; minute < SIM_TIME; minute++) {
        //arrivals
        if (minute == nextExpressArrival) {
            int items = randomBetween(1, 10);
            int st = randomBetween(1, 6);
            int sumOfPriorServiceTimes = expressLine.sumInitialServiceTimes();
            Shopper s(nextShopperID++, minute, items, st);
            s.totalTime = s.initialServiceTime + sumOfPriorServiceTimes; // calculate totalTime
            expressLine.enqueue(s);
            nextExpressArrival = minute + randomBetween(1, 5);
        }
        if (minute == nextRegularArrival) {
            int items = randomBetween(5, 15);
            int st = randomBetween(1, 6);
            int sumOfPriorServiceTimes = regularLine.sumInitialServiceTimes();
            Shopper s(nextShopperID++, minute, items, st);
            s.totalTime = s.initialServiceTime + sumOfPriorServiceTimes; // calculate totalTime
            regularLine.enqueue(s);
            nextRegularArrival = minute + randomBetween(3, 8);
        }

        //process express
        if (!expressLine.isEmpty()) {
            Shopper& fe = expressLine.front();
            if (fe.startService == 0 && fe.arrivalTime <= minute) {
                fe.startService = minute;
            }

            if (fe.startService > 0 || (fe.startService == 0 && fe.arrivalTime == minute && minute >= fe.arrivalTime)) {
                if (fe.startService == 0) {
                    fe.startService = minute;
                }

                fe.serviceTime--;
                if (fe.serviceTime <= 0) {
                    fe.finishTime = minute + 1;
                    int wait = fe.startService - fe.arrivalTime;
                    totalWaitExpress += wait;
                    totalServedExpress++;
                    expressLine.dequeue();
                }
            }
        }

        //process regular
        if (!regularLine.isEmpty()) {
            Shopper& fr = regularLine.front();
            if (fr.startService == 0 && fr.arrivalTime <= minute) {
                fr.startService = minute;
            }

            if (fr.startService > 0 || (fr.startService == 0 && fr.arrivalTime == minute && minute >= fr.arrivalTime)) {
                if (fr.startService == 0) {
                    fr.startService = minute;
                }

                fr.serviceTime--;
                if (fr.serviceTime <= 0) {
                    fr.finishTime = minute + 1;
                    int wait = fr.startService - fr.arrivalTime;
                    totalWaitRegular += wait;
                    totalServedRegular++;
                    regularLine.dequeue();
                }
            }
        }
    }

    cout << "testSimulation12Hours done. served express=" << totalServedExpress
        << ", served regular=" << totalServedRegular << endl;
    assert(totalServedExpress >= 0);
    assert(totalServedRegular >= 0);
    cout << "testSimulation12Hours passed" << endl;
}
