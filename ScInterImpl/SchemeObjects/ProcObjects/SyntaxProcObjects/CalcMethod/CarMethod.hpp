#ifndef CAR_METHOD
#define CAR_METHOD

#include"CalcMethod.hpp"
#include"../../../Object.hpp"
#include<vector>

class CarMethod : public CalcMethod{
public:
  Object* calc(std::vector<Object*>& args);
}; 

#endif
