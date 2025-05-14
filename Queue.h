//niaz hussain
//cst 202 data structures
//queue.h

#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

//manages shopper objects using a linked list
//add (enqueue) and remove (dequeue) shoppers
class Queue {
private:
    Node* head;
    Node* tail;
    int count;
public:
    Queue();
    ~Queue();
    bool isEmpty() const;
    void enqueue(const Shopper& s);
    Shopper dequeue();
    Shopper& front();
    const Shopper& front() const;
    int size() const;
    void printQueue() const;
    int sumInitialServiceTimes() const;
};

#endif