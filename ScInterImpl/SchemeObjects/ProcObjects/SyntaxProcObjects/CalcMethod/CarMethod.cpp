#include"CarMethod.hpp"
#include"../../../PairObj.hpp"
#include"../../../ListObj.hpp"
#include<iostream>


Object* CarMethod::calc(std::vector<Object*>& args){
  std::cout << "size " << args.size() << std::endl;
  if(args.size() != 1)
    throw std::string("car method expects 1 argument");
  Object* obj = args[0];
  std::cout << args[0]->print() << " " << args[0]->getType() << std::endl;
  if(obj->getType() != PAIR_OBJ && obj->getType() != LIST_OBJ)
    throw std::string("car method expects argument of type pair");
  std::cout << "type match" << std::endl;
  Object* ret;
  std::cout << "clone in car" << std::endl;
  if(obj->getType() == PAIR_OBJ)
    ret = dynamic_cast<PairObj*>(obj)->getCar()->clone();
  else
    ret = dynamic_cast<ListObj*>(obj)->begin().getObj()->clone();
  std::cout << ret->print() << std::endl;
  return ret;
}
