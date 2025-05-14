//niaz hussain
//cst 202 data structures
//shopper.h

#ifndef SHOPPER_H
#define SHOPPER_H

#include <string>
using namespace std;

//represents shopper in simulation
struct Shopper {
    int id;
    int arrivalTime;
    int items;
    int serviceTime;
    int initialServiceTime;
    int totalTime;         //total time = initialServiceTime + sum of initialServiceTimes of shoppers ahead
    int startService;
    int finishTime;

    //constructor setting everything to 0
    Shopper() {
        id = 0;
        arrivalTime = 0;
        items = 0;
        serviceTime = 0;
        initialServiceTime = 0; //initialize new member
        totalTime = 0;
        startService = 0;
        finishTime = 0;
    }

    //constructor initializing all members with values
    Shopper(int _id, int _arrivalTime, int _items, int _serviceTime) {
        id = _id;
        arrivalTime = _arrivalTime;
        items = _items;
        serviceTime = _serviceTime;        //will be decremented
        initialServiceTime = _serviceTime; //store original value
        totalTime = 0;                     //calculated before enqueue
        startService = 0;
        finishTime = 0;
    }
};

#endif