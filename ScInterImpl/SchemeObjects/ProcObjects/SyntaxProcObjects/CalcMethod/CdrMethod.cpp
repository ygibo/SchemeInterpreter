#include"CdrMethod.hpp"
#include"../../../PairObj.hpp"
#include"../../../ListObj.hpp"
#include<iostream>

Object* CdrMethod::calc(std::vector<Object*>& args){
  if(args.size() != 1)
    throw std::string("cdr method expects 1 argument");
  Object* obj = args[0];
  if(obj->getType() != PAIR_OBJ && obj->getType() != LIST_OBJ)
    throw std::string("cdr method expects argument of type pair");
  Object* ret;
  if(obj->getType() == PAIR_OBJ)
    ret = dynamic_cast<PairObj*>(obj)->getCdr()->clone();
  else
    ret = dynamic_cast<ListObj*>(obj)->getTail().clone();
  return ret;
}
