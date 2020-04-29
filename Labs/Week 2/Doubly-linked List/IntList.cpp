#include <iostream>
#include "IntList.h"

using namespace std;

//Initializes an empty list with dummy head and dummy tail
IntList::IntList() {
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);

    head = dummyHead;
    tail = dummyTail;

    head->prev = nullptr;
    head->next = tail;
    tail->prev = head;
    tail->next = nullptr;
}

//Deallocates all remaining dynamically allocated memory (all remaining IntNodes)
IntList::~IntList() {
    IntNode *temp = nullptr;
    while(dummyHead != nullptr) {
        temp = dummyHead;
        dummyHead = dummyHead->next;
        delete temp;
    }

    dummyHead = nullptr;
}

//Inserts a data value (within a new node) at the front end of the list.
//This must be an O(1) operation
void IntList::push_front(int value) {
    IntNode* temp = new IntNode(value);

    if(empty()) {
        head->next = temp;
        temp->prev = head;
        temp->next = tail;
        tail->prev = temp;
    }else {
        temp->next = head->next;
        head->next->prev = temp;
        head->next = temp;
        temp->prev = head;
    }

//    if(dummyHead == nullptr) {
//        dummyHead = new IntNode(value);
//        dummyTail = nullptr;
//    }else if(dummyTail == nullptr) {
//        dummyTail = new IntNode (value);
//        dummyHead->next = dummyTail;
//        dummyTail->next = dummyHead;
//    }else {
//        IntNode *prevHead = dummyHead;
//        IntNode *newHead = new IntNode(value);
//
//        newHead->next = prevHead;
//        prevHead->next = newHead;
//
//        dummyHead = newHead;
//    }
}

//Removes the node at the front end of the list (the node after the dummy head).
//Does nothing if the list is already empty.
//This must be an O(1) operation.
void IntList::pop_front() {
    IntNode* temp = head->next;

    if(empty()) {
        return;
    }else {
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
        temp = nullptr;
    }
//    if(dummyHead->next == nullptr) {
//        return;
//    }else if(dummyHead->next != nullptr) {
//        IntNode *temp = dummyHead;
//        dummyHead = dummyHead->next;
//        delete temp;
//    }
}

//Inserts a data value (within a new node) at the back end of the list.
// This must be an O(1) operation
void IntList::push_back(int value) {
    IntNode* temp = new IntNode(value);

    if(empty()) {
        push_front(value);
    }else {
        temp->next = tail;
        temp->prev = tail->prev;
        tail->prev = temp;
        temp->prev->next = temp;
    }
//    if(dummyHead->next != nullptr) {
//        IntNode *temp = new IntNode (value);
//        dummyTail->next = temp;
//        dummyTail = temp;
//    }else {
//        dummyHead = new IntNode (value);
//        dummyTail = dummyHead;
//    }
}

//Removes the node at the back end of the list (the node before the dummy tail).
//Does nothing if the list is already empty.
//This must be an O(1) operation
void IntList::pop_back() {
    IntNode* prevNode = tail->prev;

    if(!empty()) {
        tail->prev = prevNode->prev;
        prevNode->prev->next = tail;
        delete prevNode;
        prevNode = nullptr;
    }
}

//Returns true if the list does not store any data values (it only has dummy head and dummy tail)
//otherwise returns false.
bool IntList::empty() const {
    if(head->next != tail && tail->prev != head) {
        return false;
    }else {
        return true;
    }
}

//A global friend function that outputs to the stream all of the integer values within the list on a single line, each separated by a space.
// This function does NOT send to the stream a newline or space at the end
ostream &operator<<(ostream &out, const IntList &rhs) {
    IntNode* loc = nullptr;
    IntNode* outNode = rhs.head;

    for(loc = outNode->next; loc != rhs.tail; loc = loc->next) {
        out << loc->data;
        if(loc->next != rhs.tail) {
            out << " ";
        }
    }
    return out;
//    for(IntNode *current = rhs.dummyHead; current != nullptr; current = current->next) {
//        if(current == rhs.dummyTail) {
//            out << current->data;
//        }else {
//            out << current->data << " ";
//        }
//    }
//
//    return out;
}

//Prints to a single line all of the int values stored in the list in REVERSE order, each separated by a space.
//This function does NOT output a newline or space at the end
void IntList::printReverse() const {
    IntNode* loc = nullptr;

    for(loc = tail->prev; loc != head; loc = loc->prev) {
        cout << loc->data;
        if(loc->prev != head) {
            cout << " ";
        }
    }
//    IntNode *current = dummyHead;
//    IntNode *tail = dummyTail;
//    while(tail->next != nullptr) {
//        tail = tail->next;
//    }
//
//    while(tail != current) {
//        cout << tail->data << " ";
//        tail = tail->prev;
//    }
//
//    cout << tail->data;
}
