#include "BSTree.h"
#include "Node.h"

#include <string> 
#include <iostream>

BSTree::BSTree() {
    root = NULL;
}

BSTree::~BSTree() {
    delete root;
}

void BSTree::insert(const string &newString) {
    if (newString == "\n" ) {
        cout << "Error nullptr";

        return;
    }

    Node *newNode = new Node(newString);

    if (root == NULL) {
        root = newNode;
        root->left = NULL;
        root->right = NULL;

        root->countIncrement();
    }

    else {
        Node *temp = root;
        
        while (temp != NULL) {
            if (newNode->data == temp->data) {
                temp->countIncrement();

                return;
            }

            if (newNode->data < temp->data) {
                if (temp->left == NULL) {
                    temp->left = newNode;
                    newNode->countIncrement();
                    temp = NULL;
                }

                else {
                    temp = temp->left;
                }
            }

            else {
                if (newNode->data > temp->data) {
                    if (temp->right == NULL) {
                        temp->right = newNode;
                        newNode->countIncrement();
                        temp = NULL;
                    }

                    else {
                      temp = temp->right;
                    }
                }
            }
        }
    }
}

string BSTree::largest() const {
    string largest;
    Node *temp = root;

    if (root == NULL) {
        return "";
    }

    while (temp->right != NULL) {
        temp = temp->right;
    }

    largest = temp->data;
    return largest;
}

string BSTree::smallest() const {
    string smallest;
    Node *temp = root;

    if (root == NULL) {
        return "";
    }

    while (temp->left != NULL) {
        temp = temp->left;
    }

    smallest = temp->data;
    return smallest;

}

int BSTree::height(const string &key) const {
  if (root == NULL) {
    return -1;
  }

  Node *temp = root;

  while (temp != NULL) {
    if (temp->data == key) {
      break;
    }

    else {
      if (temp->data > key) {
        temp = temp->left;
      }

      else {
        temp = temp->right;
      }
    }
  }

    int path = 0;

    if (temp == NULL) {
      return -1;
    }

    if (temp->left == NULL && temp->right == NULL) {
      return 0;
    }

    else {
      path = height(temp);
    }

    return path - 1;
}


void BSTree::preOrder() const {
    preOrder(root);
}

void BSTree::postOrder() const {
    postOrder(root);
    cout << endl;
}

void BSTree::inOrder() const {
    inOrder(root);
}

bool BSTree::search(const string &key) const {
    bool maybe = search (root, key);

    return maybe;
}

bool BSTree::search(Node *node, const string &key) const {
    Node *temp = node;

    if (temp == NULL) {
        return false;
    }

    if (key == temp->data) {
        return true;
    }

    else {
        if (temp->data < key) {
            return search (temp->right, key);
        }

        else {
            return search (temp->left, key);
        }
    }
}

int BSTree::height(Node *node) const {
    if (node == NULL) {
        return 0;
    }

    int left = height(node->left);
    int right = height(node->right);

    if (left > right) {
        return left + 1;
    }

    else {
        return right + 1;
    }
}
/*
Node* BSTree::remove(Node *node, const string &key) {
  if (root->left == NULL && root->right == NULL) {
    delete root;
    root = NULL;
    
    return;
  }

  remove (root, key);
}*/

void BSTree::remove(const string &key) {
    if (root->left == NULL && root->right == NULL) {
        delete root;

        root = NULL;
        return;
    }

    remove (root, key);
}

Node* BSTree::remove(Node *node, const string &key) {
    if (key == "\n") {
      return root;
    }

    if(node == NULL) {
        return root;
    }

    else if(key < node->data) {
        node->left = remove(node->left, key);
    }

    else if(key > node->data) {
        node->right = remove(node->right, key);
    }

    else {
        if(node->count > 1) {
            node->countDecrement();
        } 

        else if(node->left == NULL && node->right == NULL) {
            if (root == node) {
              return root = NULL;
            }

            delete node;
            return 0;
        } 

        else if(node->left == NULL) {
            Node *temp = findMin(node->right);
            node->data = temp->data;
            node->count = temp->count;
            temp->count = 0;

            node->right = remove(node->right, temp->data);

            return node;
        } 

        else if (node->right == NULL) {
            Node *temp = findMax(node->left);
            node->data = temp->data;
            node->count = temp->count;
            temp->count = 0;

            node->left = remove(node->left, temp->data);

            return node;
        }

        else {
          Node *temp2 = findMax(node->left);
          node->data = temp2->data;
          node->count = temp2->count;
          temp2->count = 1;
          node->left = remove(node->left, temp2->data);
        }
    }

    return node;
}//dangling pointers

/*
Node* BSTree::remove(Node *node, const string &key){
   if(node == NULL || key == "/n" || node == 0){
	   return root;
   }else if(key < node->data){
	   remove(node->left, key);
   }else if(key > node->data){
	   remove(node->right, key);
   }else{
	   if(node->count > 1){
		   node->countDecrement();
	   }else if(node->left == NULL && node->right == NULL){
		   Node *parent = findParent(root, key);
		   if(parent->left == node){
			   delete node;
			   parent->left = NULL;
			   node = nullptr;
		   }else{
			   delete node;
			   parent->right = NULL;
			   node = nullptr;
		   }
	   }else if(node->left == NULL){
			Node *min = findMin(node);
			node->count = min->count;
			node->data = min->data;
			remove(node, min->data);
	   }else{
		   Node *max = findMax(node);
		   node->count = max->count;
		   node->data = max->data;
		   remove(node, max->data);
	   }
   }
    return node;
}


Node* BSTree::findParent(Node* node, const string &key){
	if(node->left->data == key || node->right->data == key){
		return node;
	}

	if(key < node->data){
		return findParent(node->left, key);
	}
	return findParent(node->right, key);
}*/

Node* BSTree::minNode(Node *node) {
    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}
//FIXME
void BSTree::preOrder(Node* node) const {
    if (node != nullptr) {
        cout << node->data << "(" << node->count << "), ";
        preOrder(node->left);
        preOrder(node->right);
    }

    else {
      return;
    }
}

void BSTree::inOrder(Node* node) const {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->data << "(" << node->count << "), ";
        inOrder(node->right);
    }

    else {
      return;
    }
}
//FIXME
void BSTree::postOrder(Node* node) const {
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << "(" << node->count << "), ";
    }

    else {
      return;
    }
}

Node* BSTree::findMax(Node* node) {
    Node *x = node;
    while (x->right != 0 && x->right != NULL) {
        x = x->right;
    }

    return x;
}

Node* BSTree::findMin(Node* node) {
    Node *y = node;
    while (y->left != 0 && y->left != NULL) {
        y = y->left;
    }

    return y;
}

