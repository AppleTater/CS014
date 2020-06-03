#ifndef Node_H
#define Node_H

#include <iostream>
#include <string>

using namespace std;

class Node {
    public:
        Node();
        Node(string data);
        
        string data;
        Node *left;
        Node *right;
        Node *parent;
        int height;
        int count;
};

#endif
