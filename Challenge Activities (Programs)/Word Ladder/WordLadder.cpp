#include "WordLadder.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <list>
#include <queue>
#include <stack>

using namespace std;

bool WordLadder::inDict(const string& s) {
    for (list<string>::iterator i = dict.begin(); i != dict.end(); i++) {
        if (s == *i) {
            return true;
        }
    }

    return false;
}

bool WordLadder::oneOff (const string &word, const string &compare) {
    int count = 0;

    for (unsigned int i = 0; i < word.size(); i++) {
        if (compare.at(i) != word.at(i)) {
            count++;
        }
    }

    if (count > 1) {
        return false;
    } else {
        return true;
    }
}

WordLadder::WordLadder(const string &fileName) {
	ifstream inputFile;
  inputFile.open(fileName.c_str());
	string currentWord = "";

	if(!inputFile.is_open()) {
		cout << "File unable to open" << endl;
		return;
	}

	while(inputFile >> currentWord) {
        if (currentWord.size() != 5) {
            cout << currentWord << "does not contain exactly 5 letters." << endl;
            return;
        }

        dict.push_back(currentWord);
    }

    inputFile.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    ofstream out;
    out.open(outputFile.c_str());

    if (!out.is_open()) {
        cout << "Error opening output file" << endl;
        return;
    }

	if (!inDict(start) || !inDict(end)) {
        cout << "Words not found in dictionary." << endl;
        return;
    }

    if (start == end) {
        out << start;
        out.close();
        return;
    }

    stack<string> words;
    words.push(start); //hold combinations

    queue<stack<string>> ladder;
    ladder.push(words); //hold all different combinations

    while (!ladder.empty()) {
        for (list<string>::iterator i = dict.begin(); i != dict.end(); i++) {
            if (oneOff(ladder.front().top(), *i)) {
                if (*i == end) {

                    stack<string> output; //temp stack for output in correct order
                    while(!ladder.front().empty()) {
                        output.push(ladder.front().top());
                        ladder.front().pop(); //switches stack words in opposite order in temp
                    }

                    while (!output.empty()) {
                        out << output.top() << endl;
                        output.pop();
                    }

                    out << *i << endl; // last word
                    out.close();
                    return;
                }

                stack<string> temp = ladder.front();

                temp.push(*i); //new combination onto queue
                ladder.push(temp);

                dict.erase(i); //erase from dictionary
                i--; //no segmentation fault
            }
        }
        ladder.pop(); //pops off older combination in queue
    }

	out << "No Word Ladder Found." << endl;
	out.close();
}
