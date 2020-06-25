#include "Jug.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

Jug::Jug(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
  capA = a;
  capB = b;
  final = c;
  cFillA = d;
  cFillB = e;
  cEmptyA = f;
  cEmptyB = g;
  cPourAB = h;
  cPourBA = i;

  createGraph(nodesList);
  //Graph();
}
/*
void Jug::Graph(){
  ofstream out("graph.dot");

  out << "digraph G {" << endl;

  for(int i = 0; i < nodesList.size(); i++){
    out << "   " << i << "[ label = \"" << nodesList[i].curPair.first << " " << 
    nodesList[i].curPair.second << "\" ];" << endl;
  }

  for(int i = 0; i < nodesList.size(); i++){
    for(int j = 0; j < 6; j++){
      out << "   " << i << " -> " << nodesList[i].neighbors[j].first << ";" << endl;
    }
  }

  out << "}" << endl;
  out.close();
}*/
Jug::~Jug() {
  /*
  for (unsigned int i = 0; i < nodesList.size(); i++) {
    delete nodesList.at(i);
  }*/
}

void Jug::createGraph(vector<Node> &nodes){
  Node node;
  Node temp;
  nodes.push_back(node);

  for(unsigned i = 0; i < nodes.size(); i++){
    temp = nodes[i];
    Node fA = temp;
    Node fB = temp;
    Node eA = temp;
    Node eB = temp;
    Node pAB = temp;
    Node pBA = temp;

    fillA(fA);
    fillB(fB);
    emptyA(eA);
    emptyB(eB);
    pourAB(pAB);
    pourBA(pBA);

    if(!exists(fA)){
      nodes.push_back(fA);
    }
    if(!exists(fB)){
      nodes.push_back(fB);
    }
    if(!exists(eA)){
      nodes.push_back(eA);
    }
    if(!exists(eB)){
      nodes.push_back(eB);
    }
    if(!exists(pAB)){
      nodes.push_back(pAB);
    }
    if(!exists(pBA)){
      nodes.push_back(pBA);
    }

    temp.neighbors[0] = pair<int, int>(index(fA), cFillA);
    temp.neighbors[1] = pair<int, int>(index(fB), cFillB);
    temp.neighbors[2] = pair<int, int>(index(eA), cEmptyA);
    temp.neighbors[3] = pair<int, int>(index(eB), cEmptyB);
    temp.neighbors[4] = pair<int, int>(index(pAB), cPourAB);
    temp.neighbors[5] = pair<int, int>(index(pBA), cPourBA);

    nodes[i] = temp;
  }
}

int Jug::index(const Node &node){
  for(unsigned i = 0; i < nodesList.size(); i++){
    if(nodesList[i].curPair.first == node.curPair.first && nodesList[i].curPair.second == node.curPair.second){
      return i;
    }
  }
  return -1;
}

bool Jug::exists(const Node &node){
  for(unsigned i = 0; i < nodesList.size(); i++){
    if(nodesList[i].curPair.first == node.curPair.first && nodesList[i].curPair.second == node.curPair.second){
      return true;
    }
  }
  return false;
}

int Jug::solve(string &solution) {
  solution = "";

  if (cFillA < 0 || cFillB < 0 || cEmptyA < 0 || cEmptyB < 0 || cPourAB < 0 || cPourBA < 0 ) {
    return -1;
  }

  if (!(0 < capA && capA <= capB)) {
    return -1;
  }

  if (!(final <= capB && capB <= 1000 && capA < capB)) {
    return -1;
  }
  
  /*
  if(capA < 1 || capB < 1 || capB > 1000 || capA <= capB || final < 0 || final > capB || cFillA < 0 || cFillB < 0 || cEmptyA < 0 || cEmptyB < 0 || cPourAB < 0 || cPourBA < 0) {

    return -1;
  }
  */
  

  const string &temp = solution;
  solution = solve(temp);

  if (solution == "") {
    return 0;
  }

  return 1;
}

string Jug::solve(const string &solution) {
   // startV has a distance of 0 from itself

   for(unsigned i = 0; i < nodesList.size(); i++){
    if(nodesList[i].curPair.first == 0 && nodesList[i].curPair.second == final){
        break;
    }else if(i == nodesList.size() - 1){
        return "";
    }
   }

   for(unsigned i = 0; i < nodesList.size(); i++){
     nodesList[i].cost = -1;
   }

   nodesList[0].cost = 0;
   //Node *current = &nodesList[0];

    vector<Node *> unvisited;
   for(unsigned i = 0; i < nodesList.size(); i++){
      Node *temp = &nodesList[i];
      unvisited.push_back(temp);
   }

   
   queue<Node*> nextInLine;
    Node *temp1 = &nodesList[0];
    nextInLine.push(temp1);
   for(int i = 0; i < 6; i++){
     Node *temp = &nodesList[nodesList[0].neighbors[i].first];
     nextInLine.push(temp);
   }

   while (!(unvisited.empty())) {
      // Visit vertex with minimum distance from startV
      Node *current = nextInLine.front();

      for(unsigned i = 0; i < unvisited.size(); i++){
        if(current->curPair.first == unvisited[i]->curPair.first && current->curPair.second == unvisited[i]->curPair.second){
          unvisited[i] = nullptr;
          unvisited.erase(unvisited.begin() + i);
        }
      }

      for(int i = 0; i < 6; i++){
         int edgeWeight = current->neighbors[i].second;
         int alternativePathDistance = current->cost + edgeWeight;
                  
         // If shorter path from startV to adjV is found,
         // update adjV's distance and predecessor
         if(nodesList[current->neighbors[i].first].cost == -1){
           nodesList[current->neighbors[i].first].cost = alternativePathDistance;
           nodesList[current->neighbors[i].first].action = current->action + Path(*current, nodesList[current->neighbors[i].first]);
           Node *temp = &nodesList[current->neighbors[i].first];
           nextInLine.push(temp);
         }else if (alternativePathDistance < nodesList[current->neighbors[i].first].cost) {
            nodesList[current->neighbors[i].first].cost = alternativePathDistance;
            nodesList[current->neighbors[i].first].action = current->action + Path(*current, nodesList[current->neighbors[i].first]);
            //adjV⇢predV = currentV
         }
      }
      nextInLine.pop();
   }

   int finalIndex = 0;
   for(unsigned i = 0; i < nodesList.size(); i++){
     if(nodesList[i].curPair.first == 0 && nodesList[i].curPair.second == final){
       finalIndex = i;
       break;
     }
   }
    /*
   for(unsigned i = 0; i < nodesList.size(); i++){
     cout << "i: " << i << " costs: " << nodesList[i].cost << endl;
   }*/
   string finalCost = to_string(nodesList[finalIndex].cost);
   string finalString = nodesList[finalIndex].action + "success " + finalCost;//no \n
   return finalString;
}

string Jug::Path(Node start, Node end){
  if(start.curPair.first == end.curPair.first && start.curPair.second == end.curPair.second){
    return "";
  }
  Node temp1 = start;
  fillA(temp1);
  if(temp1.curPair.first == end.curPair.first && temp1.curPair.second == end.curPair.second){
    return "fill A\n";
  }

  Node temp2 = start;
  fillB(temp2);
  if(temp2.curPair.first == end.curPair.first && temp2.curPair.second == end.curPair.second){
    return "fill B\n";
  }

  Node temp3 = start;
  emptyA(temp3);
  if(temp3.curPair.first == end.curPair.first && temp3.curPair.second == end.curPair.second){
    return "empty A\n";
  }

  Node temp4 = start;
  emptyB(temp4);
  if(temp4.curPair.first == end.curPair.first && temp4.curPair.second == end.curPair.second){
    return "empty B\n";
  }

  Node temp5 = start;
  pourAB(temp5);
  if(temp5.curPair.first == end.curPair.first && temp5.curPair.second == end.curPair.second){
    return "pour A B\n";
  }

  Node temp6 = start;
  pourBA(temp6);
  if(temp6.curPair.first == end.curPair.first && temp6.curPair.second == end.curPair.second){
    return "pour B A\n";
  }
  return "Error\n";
}

void Jug::fillA(Node &node) {
  node.curPair.first = capA;
}

void Jug::fillB(Node &node) {
	node.curPair.second = capB;
}

void Jug::emptyA(Node &node) {
	node.curPair.first = 0;
}

void Jug::emptyB(Node &node) {
	node.curPair.second = 0;
}

void Jug::pourAB(Node &node) {
	int A = node.curPair.first;
	int B = node.curPair.second;

	if(node.curPair.first + node.curPair.second <= capB){
		B = node.curPair.first + node.curPair.second;
    A = 0;
	}else if(node.curPair.second != capB){
		A = node.curPair.first - (capB-node.curPair.second);
		B = capB;
  }
	node.curPair.first = A;
  node.curPair.second = B;
}

void Jug::pourBA(Node &node) {
	int A = node.curPair.first;
	int B = node.curPair.second;
	
	if(node.curPair.first + node.curPair.second <= capA){
		A = node.curPair.first + node.curPair.second;
    B = 0;
	}else if(node.curPair.first != capA){
    A = capA;
		B = node.curPair.second - (capA-node.curPair.first);
  }
	node.curPair.first = A;
  node.curPair.second = B;
}
/*
#include "Jug.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

Jug::Jug(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
  capA = a;
  final = c;
  cFillA = d;
  cFillB = e;
  cEmptyA = f;
  cEmptyB = g;
  cPourAB = h;
  cPourBA = i;

  Node *fillA = new Node("fill A");
  Node *fillB = new Node ("fill B");
  Node *emptyA = new Node ("empty A");
  Node *emptyB = new Node ("empty B");
  Node *pourAB = new Node ("pour A B");
  Node *pourBA = new Node ("pour B A");

  action.push_back(fillA);
  action.push_back(fillB);
  action.push_back(emptyA);
  action.push_back(emptyB);
  action.push_back(pourAB);
  action.push_back(pourBA);

  for (unsigned int i = 0; i < action.size(); i++) {
    for (unsigned int j = 0; j < action.size(); j++) {
      if (!(i == j)) {
        action.at(i)->neighbors.push_back(action.at(j));
      }
    }
  }

  pair<int, int> t;

  t.first = 0;
  t.second = 0;
  visitedPairs.push_back(t);
}

Jug::~Jug() {
  for (unsigned int i = 0; i < action.size(); i++) {
    delete action.at(i);
  }
}

int Jug::solve(string &solution) {
  solution = "";

  if (cFillA < 0 || cFillB < 0 || cEmptyA < 0 || cEmptyB < 0 || cPourAB < 0 || cPourBA < 0 ) {
    return -1;
  }

  if (!(0 < capA && capA <= capB)) {
    return -1;
  }

  if (!(final <= capB && capB <= 1000)) {
    return -1;
  }

  const string &temp = solution;
  solution = solve(temp);

  if (solution == "") {
    return 0;
  }

  return 1;
}

string Jug::solve(const string &solution) {
  
}

bool Jug::previous(const pair<int, int> &p) {
  for (unsigned int i = 0; i < visitedPairs.size(); i++) {
    if (p == visitedPairs.at(i)) {
      return true;
    }
  }

  return false;
}

Paths Jug::doAction(const pair<int, int> &p, Node *node1) {
	Paths temp;

  temp.n = node1;

  if (node1->action == "fill A" ) {
    temp.curPair = fillA(p);
    temp.cost = cFillA;
    temp.str = "fill A";
    return temp;
  }

  if (node1->action == "fill B") {
    temp.curPair = fillB(p);
    temp.cost = cFillB;
    temp.str = "fill B";
    return temp;
  }

  if (node1->action == "empty A") {
    temp.curPair = emptyA(p);
    temp.cost = cEmptyA;
    temp.str = "empty A";
    return temp;
  }

  if (node1->action == "empty B") {
    temp.curPair = emptyB(p);
    temp.cost = cEmptyB;
    temp.str = "empty B";
    return temp;
  }
  
  if (node1->action == "pour A B") {
    temp.curPair = pourAB(p);
    temp.cost = cPourAB;
    temp.str = "pour A B";
    return temp;
  }

  if (node1->action == "pour B A") {
    temp.curPair = pourBA(p);
    temp.cost = cPourBA;
    temp.str = "pour A B";
    return temp;
  }
}

pair <int, int> Jug::makePair(int x, int y) {
  pair<int, int> temp;

  temp.first = x;
  temp.second = y;

  return temp;
}

pair<int, int> Jug::fillA(const pair<int, int> &p) {
	return makePair(capA, p.second);
}

pair<int,int> Jug::fillB(const pair<int,int> &p) {
	return makePair(p.first, capB);
}

pair<int,int> Jug::emptyA(const pair<int,int> &p) {
	return makePair(0, p.second);
}

pair<int,int> Jug::emptyB(const pair<int,int> &p) {
	return makePair(p.first, 0);
}

pair<int,int> Jug::pourAB(const pair<int,int> &p) {
	int A = 0;
	int B = 0;

	if(p.first + p.second <= capB){
		B = p.first + p.second;
	}else{
		A = p.first - capB;
		B = capB;
	}
	return makePair(A, B);
}

pair<int,int> Jug::pourBA(const pair<int,int> &p) {
	int A = 0;
	int B = 0;
	
	if(p.first + p.second <= capA){
		A = p.first + p.second;
	}else{
		A = capA;
		B = p.second - capA;
	}
	return makePair(A, B);
}*/
