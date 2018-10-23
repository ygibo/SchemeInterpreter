#include"SetObj.hpp"

SetObj::~SetObj(){
  if(val != NULL)
    delete val;
}

void SetObj::setSymbolName(std::string name){
  symbolName = name;
}

void SetObj::setValue(Object* obj){
  val = obj;
}

Object* SetObj::eval(Env* env){
  Object* obj = env->searchSymbol(symbolName);
  if(obj == NULL){
    // eval error: 未定義変数へのアクセス
    throw std::string("Assigning values to undefined symbols in Set!");
  }
  Env new_env(env);
  env->setSymbol(symbolName, val->eval(&new_env));
  return NULL;
}

std::string SetObj::print(){
  return "(#set!: " + symbolName + " " + val->print() + ")";
}

Object* SetObj::clone(){
  SetObj* obj = new SetObj();
  obj->symbolName = symbolName;
  obj->val = val->clone();
  return obj;
}
