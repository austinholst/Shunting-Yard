//Token.h
#ifndef HEADER_GUARD
#define HEADER_GUARD

#include <iostream>
#include <ctype.h>

using namespace std;

class Token {
 public:
  Token(){};
  void setOperator(char newToken);
  void setNum(int newNum);
  char getChar();
  int getPrec();
  int getAssoc();
  int getType();
  int getNum();
 private:
  char token;
  int precedence = 0;
  int associativity = 0;
  int type;
  int number = -1;
};

#endif
