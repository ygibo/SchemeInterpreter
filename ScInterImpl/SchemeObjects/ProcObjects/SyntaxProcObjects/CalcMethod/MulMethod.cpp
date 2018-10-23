#include"MulMethod.hpp"
#include"../../../SelfEvalObjects/NumberObjects/NumberObj.hpp"
#include"../../../SelfEvalObjects/NumberObjects/IntegerObj.hpp"
#include"NumberConverter.hpp"
#include<iostream>

Object* MulMethod::calc(std::vector<Object*>& args){
  std::cout << "mul calcurate" << std::endl;
  if(args.size() == 0)
    return new IntegerObj(1);
  NumberConverter converter;
  std::cout << "check" << std::endl;
  if(!converter.isNumberObj(args))
    throw std::string("adding object is not number in (*) method.");
  std::cout << "check end" << std::endl;
  if(args.size() == 1)
    return args[0]->clone();
  NumberObj* ans = dynamic_cast<NumberObj*>(args[0]->clone());
  std::cout << "start" << std::endl;
  for(int i = 1; i < args.size(); ++i){
    std::cout << "mul calc " << i << std::endl;
    converter.mul(ans, dynamic_cast<NumberObj*>(args[i]));
  }
  return ans;
}
