#include"ListProcObj.hpp"


Object* ListProcObj::eval(Env* env){
  return clone();
}

std::string ListProcObj::print(){
  return std::string("(#list factory)");
}

Object* ListProcObj::clone(){
  return new ListProcObj();
}

Object* ListProcObj::execute(ListObj& param_list, Env* env){
  return param_list.clone();
}
