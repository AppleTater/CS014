#ifndef AVLTree_H
#define AVLTree_H

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"

using namespace std;

class AVLTree {
  private:
    Node* root;
    Node* findUnbalanced(Node*);
    int height(Node*) const;
    void rotate(Node*);
    Node* rotateLeft(Node*);
    Node* rotateRight(Node*);
    void printBalanceFactors(Node*);
    void visualizeTree(ofstream &, Node*);

  public:
    AVLTree() {
      root = nullptr;
    }
    void insert(const string &); //Insert an item to the binary search tree and perform rotation if necessary.
    int balanceFactor(Node*); //Return the balance factor of a given node.
    void printBalanceFactors(); //Traverse and print the tree in inorder notation. Print the string followed by its balance factor in parentheses followed by a , and one space.
    void visualizeTree(const string &); //Generate dotty file and visualize the tree using dotty program. Call this function before and after rotation.
};

#endif

/*
findUnbalancedNode: Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.

rotate: Implement four possible imbalance cases and update the parent of the given node.

rotateLeft: Rotate the subtree to left at the given node and returns the new subroot.

rotateRight: Rotate the subtree to right at the given node and returns the new subroot.

void printBalanceFactors(Node *)

void visualizeTree(ofstream &, Node *)
*/
