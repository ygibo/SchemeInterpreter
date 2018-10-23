#ifndef PLUS_METHOD
#define PLUS_METHOD

#include"CalcMethod.hpp"
#include"../../../Object.hpp"
#include<vector>

class PlusMethod : public CalcMethod{
public:
  Object* calc(std::vector<Object*>& args);
}; 

#endif
