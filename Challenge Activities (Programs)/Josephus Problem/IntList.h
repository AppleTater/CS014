#ifndef INTLIST_H
#define INTLIST_H
#include <string>

using namespace std;

struct IntNode {
    string name;
    IntNode *next;
    IntNode(string name) : name(name), next(0) {}
};

class IntList{
    public:
        IntList();
        ~IntList();
        void push_back(string name);
        void remove(int start, int numToSkip);
        friend ostream & operator<<(ostream &out, const IntList &rhs);
    private:
        IntNode *head;
        IntNode *tail;
};

#endif
