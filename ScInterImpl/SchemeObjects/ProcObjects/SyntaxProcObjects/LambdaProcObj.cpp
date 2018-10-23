#include"LambdaProcObj.hpp"
#include"../LambdaObj.hpp"
#include"../../SymbolObj.hpp"
#include<iostream>

void setParamToLambda(LambdaObj* lambda, ListObj& list_obj){
  ListObj::Iterator iter = list_obj.begin();
  while(!iter.isEmpty()){
    Object* obj = iter.getObj();
    if(obj->getType() != SYMBOL_OBJ){
      //throw SyntaxError();
      throw std::string("A value that is not a symbol is set in the parameter.");
    }
    lambda->addParam(((SymbolObj*)(obj))->getId());
    iter.next();
  }
}

void setBodyToLambda(LambdaObj* lambda, ListObj& list_obj){
  ListObj::Iterator iter = list_obj.begin();
  while(!iter.isEmpty()){
    Object* obj = iter.getObj()->clone();
    lambda->addBody(obj);
    iter.next();
  }
}

std::string LambdaProcObj::print(){
  return "(#lambda factory)";
}

Object* LambdaProcObj::clone(){
  return new LambdaProcObj();
}

Object* LambdaProcObj::execute(ListObj& paramList, Env* e){
  LambdaObj* lambda = new LambdaObj();
  ListObj list_obj = paramList.getTail();
  Object* param_obj = paramList.getHead();
  
  if(param_obj->getType() != LIST_OBJ){
    delete lambda;
    delete param_obj;
    throw std::string("There is no parameter in the lambda expression.");
  }
  
  try{
    ListObj* params = dynamic_cast<ListObj*>(param_obj);
    setParamToLambda(lambda, *params);
  }catch(std::string& str){
    delete lambda;
    delete param_obj;
    throw str;
  }
  setBodyToLambda(lambda, list_obj);
  return lambda;
}
    
  
