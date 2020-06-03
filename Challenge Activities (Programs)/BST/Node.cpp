#include "Node.h"

Node::Node(string newData) {
    data = newData;
    count = 0;

    left = NULL;
    right = NULL;
}

void Node::countIncrement() {
    count++;
}

void Node::countDecrement() {
    count--;
}
