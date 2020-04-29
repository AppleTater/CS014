#include "IntList.h"
#include <string>
#include <iostream>

using namespace std;

// IntList();
IntList::IntList(){
    head = nullptr;
    tail = nullptr;
}

// ~IntList();
IntList::~IntList(){
	tail->next = nullptr;
    while(head != nullptr){
        IntNode *temp = head;
		head = head->next;
		delete temp;
		if(head == nullptr){
			tail = nullptr;
		}
    }
}

// void push_back(int value);
void IntList::push_back(string name){
    IntNode *temp = new IntNode(name);
    if(head == nullptr){
        head = temp;
        tail = temp;
    }else if(head == tail){
        temp->next = head;
        head->next = temp;
        tail = temp;
    }else{
        tail->next = temp;
        temp->next = head;
        tail = temp;
    }
}

void IntList::remove(int start, int numToSkip){
	IntNode *prev = head;
	IntNode *curr = nullptr;

	//Puts the curr an prev pointer in the right place to start counting
	if(start == 1){
		prev = tail;
	}else{
		for(int i = 2; i < start; i++){
			prev = prev->next;
		}
	}
	curr = prev->next;

	//counts the number of persons to skip and deletes them
	bool isBeginning = true;
	while(head != tail){
		//counts the number of people to skip
		for(int i = 0; i < numToSkip; i++){
			prev = prev->next;
		}

		//deletes the correct person
		curr = prev->next;
		IntNode *temp = curr;
		prev->next = curr->next;
		if(curr == head){
			head = curr->next;
		}else if(curr == tail){
			tail = prev;
		}
		curr = curr->next;
		delete temp;
		temp = nullptr;
		//To make sure there isn't a counting error when deleting
		//Without it, it counts an extra person because curr is currently after the one it deleted
		if(isBeginning == true){
			numToSkip--;
			isBeginning = false;
		}
	}
}

//prints the names of everybody in the linked list
ostream & operator<<(ostream &out, const IntList &rhs){
    IntNode *curr = rhs.head;
    for(curr = rhs.head; curr != rhs.tail; curr = curr->next){
        out << curr->name << endl;
    }
    out << rhs.tail->name;
    return out;
}
