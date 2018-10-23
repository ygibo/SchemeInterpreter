#ifndef MINUS_METHOD
#define MINUS_METHOD

#include"CalcMethod.hpp"
#include"../../../Object.hpp"
#include<vector>

class MinusMethod : public CalcMethod{
public:
  Object* calc(std::vector<Object*>& args);
}; 

#endif
