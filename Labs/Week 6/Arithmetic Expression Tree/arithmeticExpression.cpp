#include "arithmeticExpression.h"

#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <iostream>

using namespace std;

/* Initializes an empty tree and sets the infixExpression
to the value of parameter passed in. */
arithmeticExpression::arithmeticExpression(const string &value) {
  root = 0;
  infixExpression = value;
}

/* Converts the infixExpression to its equivalent postfix string
and then generates the tree and assigns the root node to the 
root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree() {
    // string postfix = infix_to_postfix();
    // stack<TreeNode> operands;

    // for(unsigned i = 0; i < postfix.size(); i++){
    //     TreeNode temp = TreeNode(postfix[i], i);
    //     if(postfix[i] != '/' && postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*'){
    //         operands.push(temp);
    //     }else{
    //         TreeNode leftNode = operands.top();
    //         temp.left = &leftNode;
    //         operands.pop();
    //         TreeNode rightNode = operands.top();
    //         temp.right = &rightNode;
    //         operands.pop();

    //         root = &temp;
    //         operands.push(temp);
    //     }
    // }

  infixExpression = infix_to_postfix();
  stack<TreeNode*> treeStack;
  char letter = 'a';
  char c;
  
  for(unsigned i = 0; i < infixExpression.size(); i++) {
    c = infixExpression.at(i);
    if(c == '+' || c == '-' || c == '*' || c == '/') {
      TreeNode* treeNode = new TreeNode(c, letter);
      treeNode->right = treeStack.top();
      treeStack.pop();
      treeNode->left = treeStack.top();
      treeStack.pop();
      treeStack.push(treeNode);
      letter++;
    }else {
      TreeNode* treeNode = new TreeNode(c, letter);
      letter++;
      treeStack.push(treeNode);
    }
  }
  root = treeStack.top();
  treeStack.pop();
}


/* Calls the recursive infix function. */
void arithmeticExpression::infix() {
    infix(root);
}

/* Calls the recursive prefix function. */
void arithmeticExpression::prefix() {
    prefix(root);
}

/* Calls the recursive postfix function. */
void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

/* Helper function that outputs the infix notation of 
the arithmetic expression tree
by performing the inorder traversal of the tree.
An opening and closing parenthesis must be added at the 
beginning and ending of each expression. */
void arithmeticExpression::infix(TreeNode *curr) {
    if (curr->left != 0 && curr->right != 0) {
        cout << "(";

        infix(curr->left);
        cout << curr->data;

        infix(curr->right);
        cout << ")";
    }

    else {
        cout << curr->data;
    }
}

/* Helper function that outputs the prefix notation of 
the arithmetic expression tree
by performing the preorder traversal of the tree. */
void arithmeticExpression::prefix(TreeNode *curr) {
    if (curr->left != 0 && curr->right != 0) { //print top
        cout << curr->data;
        prefix(curr->left);
        prefix(curr->right);
    }

    else {
        cout << curr->data;
    }
}

/* Helper function that outputs the postfix notation of 
the arithmetic expression tree
by performing the postorder traversal of the tree. */
void arithmeticExpression::postfix(TreeNode *curr) {
    if (curr->left != 0 && curr->right != 0) { //if curr is internal
        postfix(curr->left);
        postfix(curr->right);

        cout << curr->data;
    }

    else {
        cout << curr->data;
    }
}

void arithmeticExpression::visualizeTree(ofstream &outFS, TreeNode *n) {
    outFS << n->key << " [label=\"" << n->data << "\"];" << endl;

    if(n->left != 0){
        outFS << "\"" << n->key << "\"" << " -> " << "\"" << n->left->key << "\"" << ";" << endl;
        visualizeTree(outFS, n->left);
    }

    if(n->right != 0){
        outFS << "\"" << n->key << "\"" << " -> " << "\"" << n->right->key << "\"" << ";" << endl;
        visualizeTree(outFS, n->right);
    }

/*
    if(n->left != 0){
        outFS << "\"" << n->data << "\"" << " -> " << "\"" << n->left->data << "\"" << ";" << endl;
        visualizeTree(outFS, n->left);
    }

    if(n->right != 0){
        outFS << "\"" << n->data << "\"" << " -> " << "\"" << n->right->data << "\"" << ";" << endl;
        visualizeTree(outFS, n->right);
    }*/
}

