#ifndef JUG_H
#define JUG_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Node {
  pair<int, int> curPair; //stores capacity of left and right jug at this node
  pair<int, int> neighbors[6]; //first int stores index of neighbor, and second stores cost of neighbor
  string action = "";
  int cost = -1;

  Node *previous = NULL; 
  Node (string s) {
    action = s;
  }

  Node(){
    action = "";
    curPair.first = 0;
    curPair.second = 0;
  }
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        //anything else you need
        int capA;
        int capB;
        int final;
        int cFillA;
        int cFillB;
        int cEmptyA;
        int cEmptyB;
        int cPourAB;
        int cPourBA;
        vector<Node> nodesList; //this is the adjacency list of nodes

        void createGraph(vector<Node> &nodes);
        string solve(const string &solution);
        //void setPrevious();

        int index(const Node &node);
        bool exists(const Node &node);
        void fillA(Node &node);
        void fillB(Node &node);
        void emptyA(Node &node);
        void emptyB(Node &node);
        void pourAB(Node &node);
        void pourBA(Node &node);
        //void Graph();
        string Path(Node, Node);
};

#endif
/*
#ifndef JUG_H
#define JUG_H

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Node {
  vector<Node*> neighbors;
  string action;
  Node (string s) {
    action = s;
  }
};

struct Paths {
  pair<int, int> curPair;
  string str;
  int cost;
  Node *n;

  Paths() {
    pair<int, int> temp;
    temp.first = 0;
    temp.second = 0;

    str = "";
    cost = 0;
    n = NULL;
  }
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        //anything else you need
        int capA;
        int capB;
        int final;
        int cFillA;
        int cFillB;
        int cEmptyA;
        int cEmptyB;
        int cPourAB;
        int cPourBA;

        vector<Paths> v;
        vector<pair<int, int>> visitedPairs;
        vector <Node*> action;
        string solve(const string &solution);
        bool previous(const pair<int, int> &p);
        Paths doAction(const pair<int, int> &p, Node *node1);

        pair<int, int> makePair(int, int);
        pair<int,int> fillA(const pair<int,int> &p);
        pair<int,int> fillB(const pair<int,int> &p);
        pair<int,int> emptyA(const pair<int,int> &p);
        pair<int,int> emptyB(const pair<int,int> &p);
        pair<int,int> pourAB(const pair<int,int> &p);
        pair<int,int> pourBA(const pair<int,int> &p);
};

#endif*/
