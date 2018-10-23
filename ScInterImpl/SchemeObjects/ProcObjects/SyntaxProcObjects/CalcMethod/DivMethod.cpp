#include"DivMethod.hpp"
#include"../../../SelfEvalObjects/NumberObjects/NumberObj.hpp"
#include"../../../SelfEvalObjects/NumberObjects/IntegerObj.hpp"
#include"NumberConverter.hpp"
#include<iostream>

Object* DivMethod::calc(std::vector<Object*>& args){
  if(args.size() == 0)
    throw std::string("expects at 1 argument, given 0 (/) method");
  NumberConverter converter;
  if(!converter.isNumberObj(args))
    throw std::string("adding object is not number in (/) method.");
  if(args.size() == 1){
    /*IntegerObj* ret = new IntegerObj(0);
    NumberObj* num_obj = dynamic_cast<NumberObj*>(args[0]);
    NumberConverter::minus(ret, num_obj);*/
    return new IntegerObj(0);//args[0]->clone();
  }
  
  NumberObj* ans = dynamic_cast<NumberObj*>(args[0]->clone());
 
  for(int i = 1; i < args.size(); ++i){
    converter.div(ans, dynamic_cast<NumberObj*>(args[i]));
  }
  return ans;
}
