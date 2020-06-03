#include "AVLTree.h"
#include "Node.h"

#include <iostream>
#include <fstream>

using namespace std;

//Don't need this, I already defined in the header file
// AVLTree::AVLTree() {
//     root = 0;
// }

void AVLTree::insert(const string &str) {
    Node* unbalanced = nullptr;

    if (root == nullptr) {
        root = new Node(str);
        return;
    }
    else {
        Node* curr = root;

        while (curr != nullptr) {
            if (str == curr->data) {
                return;
            }

            if (str < curr->data) {
                if (curr->left == nullptr) {
                    curr->left = new Node(str);
                    curr->left->parent = curr;

                    unbalanced = nullptr;
                    unbalanced = findUnbalanced(curr->left);

                    if (unbalanced != nullptr) {
                        rotate(unbalanced);
                    }
                    return;
                }
                else {
                    curr = curr->left;
                }
            }
            else {
                if (curr->right == nullptr) {
                    curr->right = new Node(str);
                    curr->right->parent = curr;

                    unbalanced = nullptr;
                    unbalanced = findUnbalanced(curr->right);

                    if (unbalanced != nullptr) {
                        rotate(unbalanced);
                    }

                    return;
                }
                else {
                    curr = curr->right;
                }
            }
        }
    }
}

Node *AVLTree::findUnbalanced(Node* node) {
    if (node == 0) {
        return 0;
    }

    int balance = balanceFactor(node);

    if (balance == -2 || balance == 2) {
        return node;
    }

    else {
        return findUnbalanced(node->parent);
    }
}

int AVLTree::balanceFactor(Node *node) {
    if (node == NULL) {
        return 0;
    }

    int leftTall = height(node->left);
    int rightTall = height(node->right);
    return leftTall - rightTall;
}

void AVLTree::printBalanceFactors() {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *node) {
    if (node) {
        printBalanceFactors(node->left);

        cout << node->data << "(" << balanceFactor(node) << "), ";
        
        printBalanceFactors(node->right);
   }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS (outputFilename.c_str());
    if (!outFS.is_open()) {
        cout<< "Error" << endl;
        return;
    }

    outFS << "digraph G {" << endl;
    visualizeTree (outFS,root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if (n) {
        if (n->left) {
            visualizeTree(outFS,n->left);
            outFS << n->data << " -> " << n->left->data << ";" << endl;    
        }

        if (n->right) {
            visualizeTree(outFS, n->right);
            outFS << n->data << " -> " << n->right->data << ";" << endl;    
        }
    }
}

int AVLTree::height(Node *node) const {
  int totalHeight = 0;

  if(node != nullptr) {
    int leftTall = height(node->left);
    int rightTall = height(node->right);
    if(leftTall > rightTall) {
      totalHeight += leftTall + 1;
    }else {
      totalHeight += rightTall + 1;
    }
  }

  return totalHeight;
    // int leftTall = height(node->left);
    // int rightTall = height(node->right);

    // if (node == 0) {
    //     return -1;
    // }

    // if (leftTall > rightTall) {
    //     return leftTall + 1;
    // }

    // //reach end of non-void fnct without return
    // // else if (leftTall < rightTall) {
    // //     return rightTall + 1;
    // // }

    // //assuming nullptr and leftTall > rightTall account for n-1 cases, final would be:
    // return rightTall + 1;
}

void AVLTree::rotate (Node* node) {
  visualizeTree("graph.dot");
    if(balanceFactor(node) == 2) {
        if(balanceFactor(node->left) == 1) { // 2, 1 right
            rotateRight(node);
        }else if(balanceFactor(node->left) == -1) { // 2, -1 rotate left, then right
            rotateLeft(node->left);
            rotateRight(node);
        }
    }

    if(balanceFactor(node) == -2) {
        if(balanceFactor(node->right) == 1) {
            rotateRight(node->right);
            rotateLeft(node);
        }else if(balanceFactor(node->right) == -1) {
            rotateLeft(node);
        }
    }
  visualizeTree("graph1.dot");
}

Node* AVLTree::rotateLeft (Node* node) {
    Node* temp = nullptr;

    temp = node->right;
    node->right = temp->left;

    if (node != root) {
        if (node->parent->left == node) {
            node->parent->left = temp;
        }

        if (node->parent->right == node) {
            node->parent->right = temp;
        }
    }

    temp->parent = node->parent;
    node->parent = temp;
    temp->left = node;

    if (node == root) {
        root = temp;
    }

    return temp;
}

Node* AVLTree::rotateRight (Node* node) {
    Node* temp = nullptr;

    temp = node->left;
    node->left = temp->right;

    if (node != root) {
        if (node->parent->left == node) {
            node->parent->left = temp;
        }

        if (node->parent->right == node) {
            node->parent->right = temp;
        }
    }

    temp->parent = node->parent;
    node->parent = temp;
    temp->right = node;

    if (node == root) {
        root = temp;
    }

    return temp;
}
