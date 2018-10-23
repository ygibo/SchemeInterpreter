#include"CharObj.hpp"

Object* CharObj::eval(Env* env){
  return clone();
}

std::string CharObj::print(){
  std::string ret;
  ret += c;
  return ret;
}

Object* CharObj::clone(){
  return new CharObj(c);
}
