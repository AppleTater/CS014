#include "Node.h"

Node::Node() {
    data = "";
    count = 0;
    left = 0;
    right = 0;
    parent = 0;
    height = 0;
}

Node::Node(string data) {
    this->data = data;
    count = 0;
    left = 0;
    right = 0;
    height = 0;
    parent = 0;
}
