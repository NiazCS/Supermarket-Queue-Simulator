//niaz hussain
//cst 202 data structures
//hussainn_lab5.cpp

#include <iostream>
#include "Queue.h"
#include "TestClass.h"

using namespace std;

//returns a random integer in minVal maxVal
int randomBetween(int minVal, int maxVal) {
    return minVal + (rand() % (maxVal - minVal + 1));
}

//run 720 minute simulation then call tests
const int SIMULATION_TIME = 720;

int main() {
	srand(20000); //nicer output
    Queue expressLine;
    Queue regularLine;

    int nextExpressArrival = randomBetween(1, 5);
    int nextRegularArrival = randomBetween(3, 8);
    int nextShopperID = 1;

    int totalServedExpress = 0;
    int totalServedRegular = 0;
    int totalWaitExpress = 0;
    int totalWaitRegular = 0;

    cout << "simulation starting" << endl;
    cout << "total time: " << SIMULATION_TIME << " minutes." << endl;
    cout << "express arrivals: every 1-5 mins, service time: 1-6 mins." << endl;
    cout << "regular arrivals: every 3-8 mins, service time: 1-6 mins." << endl;

    //looping from 0 to SIMULATION_TIME, iterations as minutes
    for (int minute = 0; minute < SIMULATION_TIME; minute++) {

        if (minute > 0 && minute % 10 == 0) {
            cout << "\nminute " << minute << " status" << endl;
            cout << "express line status: ";
            expressLine.printQueue();
            cout << "regular line status: ";
            regularLine.printQueue();
            cout << "************************" << endl;
        }

        //arrivals
        if (minute == nextExpressArrival) {
            int items = randomBetween(1, 10);
            int st = randomBetween(1, 6); //get initial service time
            int sumOfPriorServiceTimes = expressLine.sumInitialServiceTimes();
            Shopper s(nextShopperID++, minute, items, st);
            s.totalTime = s.initialServiceTime + sumOfPriorServiceTimes; //set totalTime based on formula
            expressLine.enqueue(s);
            cout << "minute " << minute << ": shopper " << s.id
                << " arrives at express [q:" << expressLine.size() << "]"
                << " (service time: " << s.initialServiceTime << " mins, calculated total time: " << s.totalTime << " mins)." << endl;
            nextExpressArrival = minute + randomBetween(1, 5);
        }
        if (minute == nextRegularArrival) {
            int items = randomBetween(5, 15);
            int st = randomBetween(1, 6); //get initial service time
            int sumOfPriorServiceTimes = regularLine.sumInitialServiceTimes();
            Shopper s(nextShopperID++, minute, items, st);
            s.totalTime = s.initialServiceTime + sumOfPriorServiceTimes; //set totalTime based on formula
            regularLine.enqueue(s);
            cout << "minute " << minute << ": shopper " << s.id
                << " arrives at regular [q:" << regularLine.size() << "]"
                << " (service time: " << s.initialServiceTime << " mins, calculated total time: " << s.totalTime << " mins)." << endl;
            nextRegularArrival = minute + randomBetween(3, 8);
        }

        //process express
        if (!expressLine.isEmpty()) {
            Shopper& fe = expressLine.front();
            if (fe.startService == 0 && fe.arrivalTime <= minute) {
                fe.startService = minute;
                cout << "minute " << minute << ": shopper " << fe.id
                    << " starts service at express (arrived: "
                    << fe.arrivalTime << ")." << endl;
            }
            if (fe.startService > 0 ||
                (fe.startService == 0 && fe.arrivalTime == minute && minute >= fe.arrivalTime)) {
                if (fe.startService == 0) {
                    fe.startService = minute;
                    cout << "minute " << minute << ": shopper " << fe.id
                        << " starts service immediately at express (arrived: "
                        << fe.arrivalTime << ")." << endl;
                }

                fe.serviceTime--; //decrement remaining service time
                if (fe.serviceTime <= 0) { //check if service complete
                    fe.finishTime = minute + 1; //service finishes at end of this minute
                    int wait = fe.startService - fe.arrivalTime;
                    totalWaitExpress += wait;
                    totalServedExpress++;
                    cout << "minute " << minute << ": shopper " << fe.id
                        << " finishes service at express (wait: " << wait
                        << " mins, initial service: " << fe.initialServiceTime
                        << " mins, total time: " << fe.totalTime << " mins)."
                        << endl;
                    expressLine.dequeue();
                }
            }
        }

        //process regular
        if (!regularLine.isEmpty()) {
            Shopper& fr = regularLine.front();
            if (fr.startService == 0 && fr.arrivalTime <= minute) {
                fr.startService = minute;
                cout << "minute " << minute << ": shopper " << fr.id
                    << " starts service at regular (arrived: "
                    << fr.arrivalTime << ")." << endl;
            }
            if (fr.startService > 0 ||
                (fr.startService == 0 && fr.arrivalTime == minute && minute >= fr.arrivalTime)) {
                if (fr.startService == 0) {
                    fr.startService = minute;
                    cout << "minute " << minute << ": shopper " << fr.id
                        << " starts service immediately at regular (arrived: "
                        << fr.arrivalTime << ")." << endl;
                }

                fr.serviceTime--; //decrement remaining service time
                if (fr.serviceTime <= 0) { //check if service is complete
                    fr.finishTime = minute + 1;
                    int wait = fr.startService - fr.arrivalTime;
                    totalWaitRegular += wait;
                    totalServedRegular++;
                    cout << "minute " << minute << ": shopper " << fr.id
                        << " finishes service at regular (wait: " << wait
                        << " mins, initial service: " << fr.initialServiceTime
                        << " mins, total time: " << fr.totalTime << " mins)."
                        << endl;
                    regularLine.dequeue();
                }
            }
        }
    }

    int leftExpress = expressLine.size();
    int leftRegular = regularLine.size();

    cout << "\nsimulation results" << endl;
    cout << "total simulation time: " << SIMULATION_TIME << " minutes\n";
    cout << "express line: " << totalServedExpress << " served, "
        << leftExpress << " left\n";
    if (totalServedExpress > 0) {
        double avgWait = static_cast<double>(totalWaitExpress) / totalServedExpress;
        cout << "average wait (express): " << avgWait << " minutes\n";
    }
    else {
        cout << "average wait (express): n/a (0 served)\n";
    }
    cout << "\nregular line: " << totalServedRegular << " served, "
        << leftRegular << " left\n";
    if (totalServedRegular > 0) {
        double avgWait = static_cast<double>(totalWaitRegular) / totalServedRegular;
        cout << "average wait (regular): " << avgWait << " minutes\n";
    }
    else {
        cout << "average wait (regular): n/a (0 served)\n";
    }
    cout << "*************************\n";

    //call tests after simulation
    cout << "\nrunning testclass tests" << endl;
    TestClass::testEnqueueEmpty();
    TestClass::testEnqueueOneNode();
    TestClass::testDequeueSingleNode();
    TestClass::testDequeueTwoNodes();
    TestClass::testSimulation12Hours();
    cout << "tests completed" << endl;

    return 0;
}
