//Token.cpp
#include "Token.h"

//set the token to be an operator or parenthesis
void Token::setOperator(char newToken) {
  token = newToken;
  
  /*
   * Precedence is the order in which operations need to be done. Higher number
   * means it goes first
   *
   * Associativity is if the operator does things from left to right or right
   * or right to left.
   * 1 = left to right
   * 2 = right to left
   */

  if(token == '+' || token == '-') {
    precedence = 1;
    associativity = 1;
    type = 1;
  }
  else if(token == '*' || token == '/') {
    precedence = 2;
    associativity = 1;
    type = 1;
  }
  else if(token == '^') {
    precedence = 3;
    associativity = 2;
    type = 1;
  }
  else if(token == '(' || token == ')') {
    type = 2;
  }
}

//Set the number of the token
void Token::setNum(int newNum) {
  number = newNum;
  type = 0;
}

char Token::getChar() {
  return token;
}

int Token::getPrec() {
  return precedence;
}

int Token::getAssoc() {
  return associativity;
}

int Token::getType() {
  return type;
}

int Token::getNum() {
  return number;
}
