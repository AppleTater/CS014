#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <string>

#define MAX_SIZE 20

using namespace std;

template <typename T>
class stack {
    private:
    T data[MAX_SIZE];
    int size;

    public:
     //constructs an empty stack
    stack(); 
    // inserts a new element (val) of type T (T could be integer or string) into the data 
    //if the data array is full, this function should throw an overflow_error exception with error message //"Called push on full stack."
    void push(T val); 
    //removes the last element from data
    //if the data array is empty, this function should throw an outofrange exception with error message 
    //"Called pop on empty stack."
    void pop(); 
    //returns the top element of stack (last inserted element)
    //If stack is empty, this function should throw an underflow_error exception with error message 
    //"Called top on empty stack."
    T top(); 
    //returns true if the stack is empty otherwise it returns false
    bool empty(); 
};

#endif

template <typename T>
stack<T>::stack() {
    size = 0;
}

template <typename T>
void stack<T>::push(T val) {
    if (size == MAX_SIZE) {
        throw overflow_error("Called push on full stack.");
    } else {
        data[size] = val;
        size++;
    }
}

template <typename T>
void stack<T>::pop() {
    if (size == 0) {
        throw out_of_range("Called pop on empty stack.");
    } else {
        size--;
    }
}

template <typename T>
T stack<T>::top() {
    if (size == 0) {
        throw underflow_error("Called top on empty stack.");
    } else {
      return data[size - 1];
    }
}

template <typename T>
bool stack<T>::empty() {
    if (size == 0) {
        return true;
    } else {
        return false;
    }
}
