#ifndef INTEGER_OBJECT
#define INTEGER_OBJECT

#include<iostream>
#include<string>
#include"../../Object.hpp"
#include"NumberObj.hpp"
#include"../../../Environment.hpp"
#include<iostream>

class IntegerObj : public NumberObj{
private:
  int num;
public:
  IntegerObj() : NumberObj(INTEGER_TYPE) {}
  IntegerObj(int num) :
    num(num), NumberObj(INTEGER_TYPE) {}
  ~IntegerObj(){}
  Object* eval(Env* env);
  void set(int n);
  std::string print();
  Object* clone();
  int getVal();
};


#endif
  
