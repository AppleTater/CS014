#include "Heap.h"
#include "PrintJob.h"
#include <iostream>

using namespace std;

//Initializes an empty heap.
Heap::Heap() {
    numItems = 0;
}

//Inserts a PrintJob to the heap without violating max-heap properties.
void Heap::enqueue (PrintJob *item) {
    if(numItems != MAX_HEAP_SIZE) {
        if(empty()) {
            arr[numItems] = item;
            numItems++;
        }else {
            int curr = numItems;
            while(curr > 0 && arr[(curr - 1) / 2]->getPriority() < item->getPriority()) {
                arr[curr] = arr[(curr - 1) / 2];
                curr = (curr - 1) / 2;
            }
            arr[curr] = item;
            numItems++;
        }
    }
}

//Removes the node with highest priority from the heap. Follow the algorithm on priority-queue slides.
void Heap::dequeue() {
    if(!empty()) {
        if(numItems != 1) {
            arr[0] = arr[numItems - 1];
        }
        numItems--;
        trickleDown(0);
    }
}

//Returns the node with highest priority.
PrintJob* Heap::highest() {
    if(empty()) {
        return 0;
    }else {
        return arr[0];
    }
}

//Prints the PrintJob with highest priority in the following format:
//Priority: priority, Job Number: jobNum, Number of Pages: numPages
//(Add a newline at the end.)
void Heap::print() {
    if(!empty()) {
        cout << "Priority: " << highest()->getPriority()
             << ", Job Number: " << highest()->getJobNumber()
             << ", Number of Pages: " << highest()->getPages()
             << endl;
    }
}

//This function is called by dequeue function to move the new root down the heap to the appropriate location
void Heap::trickleDown(int num) {
    if(numItems < num * 2 + 2) {  //Base case with no children
        return;
    }else if(numItems == num * 2 + 2) {  //Base case with 1 child
        if(arr[num]->getPriority() < arr[numItems - 1]->getPriority()) {
            swap(num, numItems - 1);
        }
    }else {  //Recursive function call
        PrintJob* left = arr[num * 2 + 1];
        PrintJob* right = arr[num * 2 + 2];

        if(left->getPriority() > right->getPriority()) {
            //Compare the left to num
            if(arr[num]->getPriority() < arr[num * 2 + 1]->getPriority()) {
                swap(num, num * 2 + 1);
            }
            trickleDown(num * 2 + 1);
        }else {
            //Compare the right to num
            if(arr[num]->getPriority() < arr[num * 2 + 2]->getPriority()) {
                swap(num, num * 2 + 2);
            }
            trickleDown(num * 2 + 2);
        }
    }
}

//Swap children function
void Heap::swap(int num1, int num2) {
    PrintJob* temp = arr[num1];
    arr[num1] = arr[num2];
    arr[num2] = temp;
}
