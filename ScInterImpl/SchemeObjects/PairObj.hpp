#ifndef PAIR_OBJECT
#define PAIR_OBJECT

#include<string>
#include<iostream>
#include"Object.hpp"
#include"../Environment.hpp"
#include"../Lexer/Lexer.hpp"

class PairObj : public Object{
private:
  Object* car;
  Object* cdr;
public:
  PairObj();
  ~PairObj();

  void set(Lexer& lex);
  void setCar(Object* obj);
  void setCdr(Object* obj);
  Object* getCar();
  Object* getCdr();
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  bool isEmpty();
};

#endif
