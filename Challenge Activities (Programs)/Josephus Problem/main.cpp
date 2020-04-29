#include <string>
#include <fstream>
#include <iostream>
#include "IntList.h"

using namespace std;

int main(int argc, char* argv[]){
    //ifstream inputFile(argv[3]);
	string file = "";
	int numToSkip = 0;
	int countStart = 0;
    int numPeople = 0;

	cout << "Enter the file with the names: " << endl;
	cin >> file;
	ifstream inputFile(file);
    if(!inputFile.is_open()){
        cout << "Invalid File" << endl;
        return 0;
    }

	cout << "Enter the number of people in the circle: " << endl;
	cin >> numPeople;

	//makes sure the number of person to start with is greater than 0
	cout << "Number of person to start counting from: " << endl;
	cin >> countStart;
	while(countStart <= 0){
		cout << "Invalid Count. Please enter a number greater than 0." << endl;
		cout << "Number of person to start counting from: " << endl;
		cin >> countStart;
	}

	//Makes sure the number of people to skip is greater than 0
	cout << "How many people to skip?" << endl;
	cin >> numToSkip;
	while(numToSkip <= 0){
		cout << "Invalid. Please enter a number greater than 0." << endl;
		cout << "How many people to skip?" << endl;
		cin >> numToSkip;
	}

    IntList listOfPeople;
    string namesOfPeople;

    //Get the Names of the people and push them into a linked list
    for(unsigned i = 0; i < numPeople; i++){
        getline(inputFile, namesOfPeople);
        listOfPeople.push_back(namesOfPeople);
    }

	//Deletes the dead people and prints the list
	listOfPeople.remove(countStart, numToSkip);
	cout << "Survivor: " << listOfPeople << endl;
	return 0;
}

// Use a linked list (hint: circularly linked list) to solve the Josephus problem, 
// which is, “Whois the last person standing?
// "Input:
// -n​: the number of people in the initial circle;
// -a file, that contains names of people in the circle 
// (each name is a string, written on a new line)
//-the number of a person to start counting from;
// -k​: how many people to skip (if k = 2, then every second person is to be executed)
// Output: the name of the lucky survivor
