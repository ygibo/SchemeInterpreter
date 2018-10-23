#include"SymbolObj.hpp"
#include<iostream>

void SymbolObj::set(std::string name){
  id = name;
}

std::string SymbolObj::getId(){
  return id;
}

Object* SymbolObj::eval(Env* e){
  Object* obj = e->searchSymbol(id);
  if(obj == NULL){
    e->setSymbol(id, NULL);
  }
  return obj->clone();
}

std::string SymbolObj::print(){
  return id;
}

Object* SymbolObj::clone(){
  return new SymbolObj(id);
}
