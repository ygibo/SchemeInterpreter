#include"BoolObj.hpp"

bool BoolObj::getVal(){
  return bool_value;
}

Object* BoolObj::eval(Env* env){
  return clone();
}

std::string BoolObj::print(){
  return (bool_value ? "#t" : "#f");
}

Object* BoolObj::clone(){
  return new BoolObj(bool_value);
}
