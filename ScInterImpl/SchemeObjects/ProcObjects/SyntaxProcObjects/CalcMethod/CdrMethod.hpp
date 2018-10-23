#ifndef CDR_METHOD
#define CDR_METHOD

#include"CalcMethod.hpp"
#include"../../../Object.hpp"
#include<vector>

class CdrMethod : public CalcMethod{
public:
  Object* calc(std::vector<Object*>& args);
}; 

#endif
