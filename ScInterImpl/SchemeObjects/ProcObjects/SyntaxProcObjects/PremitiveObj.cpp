#include"PremitiveObj.hpp"
#include"CalcMethod/CalcMethod.hpp"
#include"CalcMethod/PlusMethod.hpp"
#include"CalcMethod/MinusMethod.hpp"
#include"CalcMethod/MulMethod.hpp"
#include"CalcMethod/DivMethod.hpp"
#include"CalcMethod/CarMethod.hpp"
#include"CalcMethod/CdrMethod.hpp"
#include"../../Object.hpp"
#include<iostream>

CalcMethod* getCalcMethod(std::string methodName){
  if(methodName == "+")
    return new PlusMethod();
  else if(methodName == "-")
    return new MinusMethod();
  else if(methodName == "*")
    return new MulMethod();
  else if(methodName == "/")
    return new DivMethod();
  else if(methodName == "car")
    return new CarMethod();
  else if(methodName == "cdr")
    return new CdrMethod();
  return NULL;
}

PremitiveObj::PremitiveObj(std::string method_name) : ProcObj(method_name){
  method = getCalcMethod(method_name);
}  

PremitiveObj::~PremitiveObj(){
  if(method != NULL)
    delete method;
}

Object* PremitiveObj::eval(Env* env){
  return clone();
}

std::string PremitiveObj::print(){
  return "#(method: " + name + ")";
}

void PremitiveObj::setMethod(std::string methodName){
  method = getCalcMethod(methodName);
}

Object* PremitiveObj::clone(){
  return new PremitiveObj(name);
}

void vectorDelete(std::vector<Object*>& vec){
  for(int i = 0; i < vec.size(); ++i){
    if(vec[i] != NULL)
      delete vec[i];
  }
}

Object* PremitiveObj::execute(ListObj& params, Env* env){
  std::vector<Object*> evaluated_params;
  ListObj::Iterator iter = params.begin();
  try{
    while(!iter.isEmpty()){
      Env new_env(env);
      Object* obj = iter.getObj()->eval(&new_env);
      if(obj == NULL){
	throw std::string("An illegal expression is set") +
	  std::string(" for a function parameter: ")
	  + name + " -> " + iter.getObj()->print();
      }
      evaluated_params.push_back(obj);
      iter.next();
    }
  }catch(std::string& s){
    vectorDelete(evaluated_params);
    throw s;
  }
  
  Object* ans = NULL;
  try{
    ans = method->calc(evaluated_params);
  }catch(std::string& s){
    std::cout << s << std::endl;
    vectorDelete(evaluated_params);
    throw s;
  }
  vectorDelete(evaluated_params);
  return ans;
}
  
  
  
