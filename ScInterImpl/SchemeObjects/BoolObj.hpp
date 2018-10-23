#ifndef BOOL_OBJECT
#define BOOL_OBJECT

#include<string>
#include<iostream>
#include"Object.hpp"
#include"../Environment.hpp"

class BoolObj : public Object{
private:
  bool bool_value;
public:
  BoolObj(bool bool_value) : bool_value(bool_value), Object(BOOL_OBJ) {};
  ~BoolObj() {};
  bool getVal();
  Object* eval(Env* env);
  std::string print();
  Object* clone();
};

#endif
