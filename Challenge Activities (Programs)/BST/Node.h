#pragma once

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {
    public:
        string data;
        int count;

        Node (string newData);

        void countIncrement();
        void countDecrement();

        Node *left;
        Node *right;
};

#endif
