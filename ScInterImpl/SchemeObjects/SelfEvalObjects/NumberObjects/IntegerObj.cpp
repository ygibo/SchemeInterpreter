#include"IntegerObj.hpp"
#include<sstream>

Object* IntegerObj::eval(Env* env){
  return static_cast<Object*>(new IntegerObj(num));
}

void IntegerObj::set(int n){
  num = n;
}

int IntegerObj::getVal(){
  return num;
}

std::string IntegerObj::print(){
  std::stringstream os;
  os << num;
  return os.str();
}

Object* IntegerObj::clone(){
  return static_cast<Object*>(new IntegerObj(num));
}
