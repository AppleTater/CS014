#ifndef LAB2_INTLIST_H
#define LAB2_INTLIST_H

#include <iostream>
using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList {
private:
    IntNode *dummyHead;
    IntNode *dummyTail;
    IntNode *head;
    IntNode *tail;
public:
    IntList();
    ~IntList();
    void push_front(int value);
    void pop_front();
    void push_back(int value);
    void pop_back();
    bool empty() const;
    friend ostream & operator<<(ostream &out, const IntList &rhs);
    void printReverse() const;
};

#endif //LAB2_INTLIST_H
