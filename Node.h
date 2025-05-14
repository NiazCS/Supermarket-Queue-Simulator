//niaz hussain
//cst 202 data structures
//node.h

#ifndef NODE_H
#define NODE_H

#include "Shopper.h"

//node class for a linked list that stores a shopper
class Node {
public:
    Shopper data;
    Node* next;

    Node() : next(nullptr) {}

    explicit Node(const Shopper& s) : data(s), next(nullptr) {}
};

#endif
