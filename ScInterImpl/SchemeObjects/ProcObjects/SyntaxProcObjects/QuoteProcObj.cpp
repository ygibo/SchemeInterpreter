#include"QuoteProcObj.hpp"

std::string QuoteProcObj::print(){
  return std::string("(#QuoteProc)");
}

Object* QuoteProcObj::clone(){
  return new QuoteProcObj();
}

Object* QuoteProcObj::eval(Env* env){
  return clone();
}

Object* QuoteProcObj::execute(ListObj& param_list, Env* env){
  if(param_list.size() != 1)
    throw std::string("expect 1 argument in quote statement");
  Object* obj = param_list.begin().getObj()->clone();
  return obj;
}
