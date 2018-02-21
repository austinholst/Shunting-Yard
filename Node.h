//Node.h
#include "Token.h"

using namespace std;

class Node {
 public:
  //Setters
  Node(Token* token);
  void setLeft(Node* node);
  void setRight(Node* node);
  void setPrevious(Node* node);
  void setNext(Node* node);
  //Getters
  Token* getToken();
  Node* getLeft();
  Node* getRight();
  Node* getNext();
  Node* getPrevious();
 private:
  Token* token;
  Node* left = NULL;
  Node* right = NULL;
  Node* previous = NULL;
  Node* next = NULL;
};
