//niaz hussain
//cst 202 data structures
//queue.cpp

#include "Queue.h"
#include <iostream>
using namespace std;

//constructor
Queue::Queue() : head(nullptr), tail(nullptr), count(0) {}

//destructor
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

//check if queue is empty
bool Queue::isEmpty() const {
    return (count == 0);
}

//add a shopper to the end of the queue
void Queue::enqueue(const Shopper& s) {
    Node* newNode = new Node(s);
    if (isEmpty()) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

//remove and return the shopper at the front of queue
Shopper Queue::dequeue() {
    if (isEmpty()) {
        cout << "error: queue underflow on dequeue attempt." << endl;
        return Shopper(); //return default shopper if queue is empty
    }
    Node* temp = head;
    Shopper frontShopper = head->data;
    head = head->next;
    if (!head) {
        tail = nullptr;
    }
    delete temp;
    count--;
    return frontShopper;
}

//return a reference to the shopper at the front of the queue
Shopper& Queue::front() {
    if (isEmpty()) {
        cout << "error: attempting front() on empty queue." << endl;
        static Shopper dummy;
        return dummy;
    }
    return head->data;
}

//return a const reference to the shopper at the front of the queue
const Shopper& Queue::front() const {
    if (isEmpty()) {
        cout << "error: attempting front() on empty queue." << endl;
        static Shopper dummy;
        return dummy;
    }
    return head->data;
}

//return the number of shoppers in the queue
int Queue::size() const {
    return count;
}

//print the ids of shoppers currently in the queue
void Queue::printQueue() const {
    if (isEmpty()) {
        cout << "[empty]" << endl;
        return;
    }
    Node* current = head;
    cout << "[front: shopper #" << current->data.id;
    current = current->next;
    while (current) {
        cout << ", shopper #" << current->data.id;
        current = current->next;
    }
    cout << " :end]" << endl;
}

//calculate the sum of initial service times for all shoppers currently in the queue
int Queue::sumInitialServiceTimes() const {
    int totalService = 0;
    Node* current = head;
    while (current != nullptr) {
        totalService += current->data.initialServiceTime;
        current = current->next;
    }
    return totalService;
}
