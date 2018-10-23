#include"PairObj.hpp"

PairObj::PairObj() : car(NULL), cdr(NULL),  Object(PAIR_OBJ){
#ifdef DEBUG
  std::cout << "pair create " << this << std::endl;
#endif 
}

PairObj::~PairObj(){
#ifdef DEBUG
  std::cout << "pair del " << this << std::endl;
  std::cout << print() << std::endl;;
#endif
  if(car != NULL){
    delete car;
    car = NULL;
  }
  if(cdr != NULL){
    delete cdr;
    cdr = NULL;
  }
#ifdef DEBUG
  std::cout << "pair del end " << this << std::endl;
#endif
}

void PairObj::set(Lexer& lex){}

void PairObj::setCar(Object* obj){
  car = obj;
}

void PairObj::setCdr(Object* obj){
  cdr = obj;
}

Object* PairObj::getCar(){
  return car;
}

Object* PairObj::getCdr(){
  return cdr;
}

Object* PairObj::eval(Env* eval){
  //throw std::string("Executed Empty list");
  return clone();
}

std::string PairObj::print(){
  std::string ret;
  if(car == NULL && cdr == NULL)
    ret = "`";
  ret += "(";
  
  if(car != NULL)
    ret += car->print();
  if(car != NULL || cdr != NULL)
    ret += " . ";
  if(cdr != NULL)
    ret += cdr->print();
  ret += ")";
  return ret;
}

Object* PairObj::clone(){
  PairObj* new_pair = new PairObj();
  if(car != NULL)
    new_pair->car = car->clone();
  if(cdr != NULL)
    new_pair->cdr = cdr->clone();
  return new_pair;
}

bool PairObj::isEmpty(){
  return car == NULL && cdr == NULL;
}
