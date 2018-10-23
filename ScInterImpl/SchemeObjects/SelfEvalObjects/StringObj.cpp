#include"StringObj.hpp"

void StringObj::set(std::string s){
  str = s;
}

std::string StringObj::getString(){
  return str;
}

Object* StringObj::eval(Env* env){
  return new StringObj(str);
}
std::string StringObj::print(){
  return str;
}

Object* StringObj::clone(){
  return new StringObj(str);
}
