#ifndef NUMBER_OBJECT
#define NUMBER_OBJECT

#include"../../Object.hpp"
#include"../../../Environment.hpp"

enum NumberType{
  INTEGER_TYPE = 1, DOUBLE_TYPE = 2
};

class NumberObj : public Object{
private:
  NumberType numType;
public:
  NumberObj(NumberType numType) : numType(numType),  Object(NUMBER_OBJ) {}
  ~NumberObj() {}
  NumberType getNumberType(){ return numType; }
};


#endif
  
