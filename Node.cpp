//Node.cpp
#include "Node.h"

using namespace std;

Node::Node(Token* newToken) {
  token = newToken;
}

void Node::setLeft(Node* node) {
  left = node;
}

void Node::setRight(Node* node) {
  right = node;
}

void Node::setNext(Node* node) {
  next = node;
}

void Node::setPrevious(Node* node) {
  previous = node;
}

Token* Node::getToken() {
  return token;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

Node* Node::getPrevious() {
  return previous;
}

Node* Node::getNext() {
  return next;
}
