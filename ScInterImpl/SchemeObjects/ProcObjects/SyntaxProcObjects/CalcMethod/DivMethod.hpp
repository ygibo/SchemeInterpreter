#ifndef DIVIDE_METHOD
#define DIVIDE_METHOD

#include"CalcMethod.hpp"
#include"../../../Object.hpp"
#include<vector>

class DivMethod : public CalcMethod{
public:
  Object* calc(std::vector<Object*>& args);
}; 

#endif
