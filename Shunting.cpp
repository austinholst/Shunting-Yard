//Main.cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include "Token.h"
#include "Node.h"

/*
 *Author: Austin Holst (With help from Raveen Karnik on building the binary expression tree and prefix notation)
 *Date: Febuary 21, 2018
 *Code: Uses the shunting yard algorithm to put expression into postfix and then builds epxression tree out of it
 *      Can then put expression into postix, prefix, or infix from that expression tree
 */


using namespace std;

//Vectors
vector<Token*> tokens;

//Prototype
Node* listing(Node* &head, Token* newToken);
Node* findEnd(Node* head);
void print(Node* head);
Node* pop(Node* head);
void printPostfix(Node* head);
void printPrefix(Node* head);
void printInfix(Node* head);

//Associativity constants
const int NONE = 0;
const int LEFT = 1;
const int RIGHT = 2;

const int NUM = 0; //number
const int OP = 1;  //operator
const int PAR = 2; //parenthesis

int main() {
  //Variables
  bool running = true;
  char* input = new char[50];
 
  cout << "Input a mathematical expression with spaces in between each term" << endl;
  
  Node* head = NULL;
  cin.getline(input, 100);
  //iterate through the expression
  for(int i = 0; i < strlen(input); i++) {
    //if its a digit set the start value and keep tack of how long the digit is
    if(isdigit(input[i]) == true) {
      int start = i;
      int length = 1;
      while(input[i + 1] != char(32) && i < strlen(input)) {
	length++;
	i++;
      }
      //When you hit a space put that digit into it's own char
      char* CharNum = new char[length];
      for(int j = 0; j < length; j++) {
	CharNum[j] = input[start + j];
      }
      //Turn that digit into an int
      int number = atoi(CharNum);
     	
      Token* token = new Token();
      token->setNum(number);
      head = listing(head, token);
    }
    //If the character is an operator
    else if(input[i] != char(32)) {
      Token* token = new Token();
      token->setOperator(input[i]);
      head = listing(head, token);
    }
  }
  
  Node* current = head;
  //Head for the list of nodes which will be in postfix notation
  Node* outputHead = NULL;
  //Head for the list of nodes that contain the 
  Node* operatorHead = NULL;
  
  //While there are tokens to be read
  while(current != NULL) {
    //If the token is a number
    if(current->getToken()->getType() == NUM) {
      listing(outputHead, current->getToken());
    }
    //If the token is a parenthesis
    else if(current->getToken()->getType() == PAR) {
      //If the token is a ( push onto operator stack
      if(current->getToken()->getChar() == '(') {
	listing(operatorHead, current->getToken());
      }
      //If the token is a )
      else {
	while(findEnd(operatorHead)->getToken()->getType() != PAR) {
	  listing(outputHead, findEnd(operatorHead)->getToken());
	  Node* end = findEnd(operatorHead);
	  end->getPrevious()->setNext(NULL);
	  delete end;
	}
	delete findEnd(operatorHead)->getToken();
	Node* end = findEnd(operatorHead);
	if(end->getPrevious() != NULL) {
	  end->getPrevious()->setNext(NULL);
	  delete end;
	}
	else {
	  operatorHead = NULL;
	}
      }
    }
    //If the token is an operator
    else {
      if(operatorHead != NULL) {
	while(((findEnd(operatorHead)->getToken()->getPrec() > current->getToken()->getPrec()) ||
	       (findEnd(operatorHead)->getToken()->getPrec() == current->getToken()->getPrec() &&
		findEnd(operatorHead)->getToken()->getAssoc() == LEFT)) &&
	      (findEnd(operatorHead)->getToken()->getChar() != '(')) {

	  listing(outputHead, findEnd(operatorHead)->getToken());
	  Node* end = findEnd(operatorHead);
	  if(end->getPrevious() != NULL) {
	    end->getPrevious()->setNext(NULL);
	    delete end;
	  }
	  else {
	    operatorHead = NULL;
	    break;
	  }
	}
      }
      listing(operatorHead, current->getToken());
    }

    
    //Move to the next node
    Node* prev = current;
    current = current->getNext();
    delete prev;
  }
  while(operatorHead != NULL) {
    listing(outputHead, findEnd(operatorHead)->getToken());
    Node* end = findEnd(operatorHead);
    if(end->getPrevious() != NULL) {
      end->getPrevious()->setNext(NULL);
      delete end;
    }
    else {
      operatorHead = NULL;
    }
  }

  print(outputHead);
  cout << "" << endl;
  
  //Creating expression tree (Thanks Raveen for showing me this method)
  Node* treeTop = findEnd(outputHead);
  current = outputHead;
  while(current != NULL) {
    if(current->getToken()->getType() == OP) {
      current->setLeft(current->getPrevious()->getPrevious());
      current->setRight(current->getPrevious());
      current->setPrevious(current->getLeft()->getPrevious());
      if(current->getPrevious() != NULL) {
	current->getPrevious()->setNext(current);
      }
      current->getLeft()->setPrevious(NULL);
      current->getLeft()->setNext(NULL);
      current->getRight()->setPrevious(NULL);
      current->getRight()->setNext(NULL);
    }
    current = current->getNext();
  }

  
  char* answer = new char[20];
  cout << "Would you like to print the expression in 'postfix' 'prefix' or 'infix' notation" << endl;
  cin.getline(answer, 20);
  if(strcmp(answer, "postfix") == 0) {
    cout << "Postfix Notation: ";
    printPostfix(treeTop);
    cout << "" << endl;
  }
  else if(strcmp(answer, "prefix") == 0) {
    cout << "Prefix Notation: ";
    printPrefix(treeTop);
    for(int i = 1; i <= tokens.size(); i++) {
      if(tokens[tokens.size()-i]->getType() == NUM) {
	cout << tokens[tokens.size()-i]->getNum() << " ";
      }
      else {
	cout << tokens[tokens.size()-i]->getChar() << " ";
      }
    }
    cout << "" << endl;
  }
  else if(strcmp(answer, "infix") == 0) {
    cout << "Infix: " << endl;
    printInfix(treeTop);
    cout << "" << endl;
  }
  else {
    cout << "That wasn't one of the options" << endl;
  }
  
  return 0;
}

//Print from the expression tree in postfix notation
void printPostfix(Node* head) {
  if(head->getLeft() != NULL) {
    printPostfix(head->getLeft());
  }
  if(head->getRight() != NULL) {
    printPostfix(head->getRight());
  }
  if(head->getToken()->getType() == NUM) {
    cout << head->getToken()->getNum() << " ";
  }
  else {
    cout << head->getToken()->getChar() << " ";
  }
}

//Print from the expression tree in infix notation
void printInfix(Node* head) {
  if(head->getLeft() != NULL) {
    cout << "(";
    printInfix(head->getLeft());
  }
  if(head->getToken()->getType() == NUM) {
    cout << head->getToken()->getNum();
  }
  else {
    cout << head->getToken()->getChar();
  }
  if(head->getRight() != NULL) {
    printInfix(head->getRight());
    cout << ")";
  }
}

//Print from the expression tree in prefix notation
void printPrefix(Node* head) {
  if(head->getRight() != NULL) {
    printPrefix(head->getRight());
  }
  if(head->getLeft() != NULL) {
    printPrefix(head->getLeft());
  }
  tokens.push_back(head->getToken());
}

//Removes the last object from the linked list
Node* pop(Node* head) {
  Node* end = findEnd(head);
  if(end->getPrevious() != NULL) {
    end->getPrevious()->setNext(NULL);
    return end;
  }
  else {
    return NULL;
  }
}

//Print out the expression after shunting yard
void print(Node* head) {
  if(head == NULL) {
    cout << "There is no nodes" << endl;
  }
  else if(head->getNext() == NULL) {
    if(head->getToken()->getType() == NUM) {
      cout << head->getToken()->getNum() << " ";
    }
    else {
      cout << head->getToken()->getChar() << " ";
    }
  }
  else {
    if(head->getToken()->getType() == NUM) {
      cout << head->getToken()->getNum() << " ";
    }
    else {
      cout << head->getToken()->getChar() << " ";
    }
    print(head->getNext());
  }
}

//Find the end of a linked list
Node* findEnd(Node* head) {
  if(head->getNext() != NULL) {
    return findEnd(head->getNext());
  }
  else {
    return head;
  }
}

//Pushing a new node to the list
Node* listing(Node* &head, Token* newToken) {
  Node* node = new Node(newToken);
  if(head == NULL) {
    head = node;
  }
  else {
    Node* end = findEnd(head);
    end->setNext(node);
    node->setPrevious(end);
  }
  return head;
}
