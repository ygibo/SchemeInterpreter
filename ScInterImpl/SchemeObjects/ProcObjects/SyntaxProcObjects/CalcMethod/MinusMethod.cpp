#include"MinusMethod.hpp"
#include"../../../SelfEvalObjects/NumberObjects/IntegerObj.hpp"
#include"NumberConverter.hpp"


Object* MinusMethod::calc(std::vector<Object*>& args){
  bool isInteger = true;
  if(args.size() == 0)
    throw std::string("expects at least 1 arguments, given 0: method (-)");
  NumberConverter converter;
  if(!converter.isNumberObj(args))
    throw std::string("subtracting object is not number in (-) method.");
  if(args.size() == 1){
    IntegerObj* ret = new IntegerObj(0);
    NumberObj* num_obj = dynamic_cast<NumberObj*>(args[0]);
    converter.minus(ret, num_obj);
    return ret;
  }

  NumberObj* ret = static_cast<NumberObj*>(args[0]->clone());
  for(int i = 1; i < args.size(); ++i){
    converter.minus(ret, dynamic_cast<NumberObj*>(args[i]));
  }
  return ret;
}
