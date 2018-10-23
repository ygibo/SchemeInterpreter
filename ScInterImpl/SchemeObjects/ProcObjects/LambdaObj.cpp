#include"LambdaObj.hpp"
#include<cassert>
#include<iostream>

LambdaObj::~LambdaObj(){
  for(int i = 0; i < body.size(); ++i){
    if(body[i] != NULL){
      delete body[i];
    }
  }
}

void LambdaObj::addParam(std::string name){
  paramName.push_back(name);
}

void LambdaObj::addBody(Object* obj){
  body.push_back(obj);
}

std::string LambdaObj::print(){
  std::string str;
  str += "(lambda (";
  for(int i = 0; i < paramName.size(); ++i){
    str += paramName[i];
    if(i < paramName.size() - 1)
      str += " ";
  }
  str += ") ";
  for(int i = 0; i < body.size(); ++i){
    str += body[i]->print();
    if(i < body.size() - 1)
      str += " ";
  }
  str += ")";
  return str;
}

Object* LambdaObj::clone(){
  LambdaObj* lambda = new LambdaObj();
  for(int i = 0; i < paramName.size(); ++i)
    lambda->addParam(paramName[i]);
  for(int i = 0; i < body.size(); ++i)
    lambda->addBody(body[i]->clone());
  return lambda;
}

Object* LambdaObj::execute(ListObj& paramList, Env* e){
#ifdef DEBUG
  std::cout << "lambda execute" << std::endl;
#endif
  Env new_env(e);
  ListObj::Iterator iter = paramList.begin();
  for(int i = 0; i < paramName.size(); ++i){
    if(iter.isEmpty()){
      throw std::string("Few parameter in Lambda procedure");
    }
    assert(iter.getObj()!=NULL&&"lambda parameter is NULL object");
    
    Object* obj = NULL;
    obj = iter.getObj()->eval(&new_env);
    if(obj == NULL){
      throw std::string("Set an Empty value for the function's parameter: ")
	+ iter.getObj()->print();
    }
    new_env.setSymbol(paramName[i], obj);
    iter.next();
  }
  
  Object* ret = NULL;
  try{
    for(int i = 0; i < body.size() - 1; ++i){
      if(body[i] != NULL){
	ret = body[i]->eval(&new_env);
	if(ret != NULL)
	  delete ret;
      }
    }
    if(body[body.size() - 1] != NULL){
      ret = body[body.size() - 1]->eval(&new_env);
    }
  }catch(std::string s){
    throw s;
  }
#ifdef DEBUG
  std::cout << "end lambda execute" << std::endl;
#endif
  return ret;
}
    
  
