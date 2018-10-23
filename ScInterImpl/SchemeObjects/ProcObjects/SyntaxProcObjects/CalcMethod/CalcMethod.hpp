#ifndef CALC_METHOD
#define CALC_METHOD

#include"../../../Object.hpp"
#include<vector>

class CalcMethod{
public:
  virtual Object* calc(std::vector<Object*>& args) = 0;
}; 

#endif
