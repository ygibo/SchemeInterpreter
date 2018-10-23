#include"SetProcObj.hpp"
#include"SyntaxObjects/SetObj.hpp"
#include"../../SymbolObj.hpp"

Object* SetProcObj::execute(ListObj& param_list, Env* env){
  Object* obj = param_list.getHead();
  if(obj->getType() != SYMBOL_OBJ){
    delete obj;
    throw std::string("Assigned to a non symbol object.");
  }
  SymbolObj* symbol = static_cast<SymbolObj*>(obj);
  SetObj* setObj = new SetObj();
  setObj->setSymbolName(symbol->getId());
  ListObj tail_list = param_list.getTail();
  ListObj::Iterator iter = tail_list.begin();
  if(iter.isEmpty()){
    delete obj;
    delete setObj;
    throw std::string("Empty value in set! statement.");
  }
  Object* value_obj = tail_list.getHead();
  Env new_env(env);
  setObj->setValue(value_obj->eval(&new_env));
  try{
    setObj->eval(env);
  }catch(std::string& s){
    delete obj;
    delete value_obj;
    delete setObj;
  } 
  return NULL;
}

  
Object* SetProcObj::eval(Env* env){
  return clone();
}

std::string SetProcObj::print(){
  return "(#set! factory)";
}

Object* SetProcObj::clone(){
  return new SetProcObj();
}
