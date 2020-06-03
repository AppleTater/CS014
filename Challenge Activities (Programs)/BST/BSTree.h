#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <iostream>
#include "Node.h"

class BSTree {
    private:
      Node *root;
      bool search(Node *node, const string &key) const;
      int height(Node *node) const;
      Node* remove(Node *node, const string &key);
	    Node* minNode(Node *node);
	    void preOrder(Node* node) const;
	    void inOrder(Node* node) const;
	    void postOrder(Node* node) const;
	
	    Node* findMax(Node* node);
	    Node* findMin(Node* node);

		//Node* findParent(Node* node, const string &key){


    public:
        BSTree();
        ~BSTree();
        void insert(const string &newString);
        void remove(const string &key);
        bool search(const string &key) const;
        string largest() const;
        string smallest() const;
        int height(const string&) const;
        void preOrder() const;
        void postOrder() const;
        void inOrder() const;
};

#endif // __BSTREE_H__
