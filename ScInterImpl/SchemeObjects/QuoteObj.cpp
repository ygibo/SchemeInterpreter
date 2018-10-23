#include"QuoteObj.hpp"
#include<iostream>

QuoteObj::~QuoteObj(){
#ifndef DEBUG
  std::cout << "quote delete " << this << std::endl;
#endif
  delete exp;
}

QuoteObj::QuoteObj() : exp(NULL), Object(QUOTE_OBJ) {
#ifdef DEBUG
  std::cout << "quote create " << this << std::endl;
#endif
}

QuoteObj::QuoteObj(Object* quotedExp) : exp(quotedExp), Object(QUOTE_OBJ) {
#ifdef DEBUG
  std::cout << "quote create " << this << std::endl;
#endif
}

Object* QuoteObj::eval(Env* env){
  if(exp == NULL)
    return NULL;
  return exp->clone();
}

std::string QuoteObj::print(){
  if(exp == NULL)
    return "";
  return exp->print();
}

Object* QuoteObj::clone(){
  if(exp == NULL)
    return NULL;
  QuoteObj* obj = new QuoteObj(exp->clone());
  return obj;
}

void QuoteObj::set(Object* obj){
  if(exp != NULL)
    delete exp;
  exp = obj;
}

