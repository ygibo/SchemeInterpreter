#ifndef MULTIPLE_METHOD
#define MULTIPLE_METHOD

#include"CalcMethod.hpp"
#include"../../../Object.hpp"
#include<vector>

class MulMethod : public CalcMethod{
public:
  Object* calc(std::vector<Object*>& args);
}; 

#endif
