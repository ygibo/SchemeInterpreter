#include"PlusMethod.hpp"
#include"../../../SelfEvalObjects/NumberObjects/NumberObj.hpp"
#include"../../../SelfEvalObjects/NumberObjects/IntegerObj.hpp"
#include"NumberConverter.hpp"
#include<iostream>

Object* PlusMethod::calc(std::vector<Object*>& args){
  bool isInteger = true;
  if(args.size() == 0)
    return new IntegerObj(0);
  NumberConverter converter;

  if(!converter.isNumberObj(args))
    throw std::string("adding object is not number in (+) method.");

  if(args.size() == 1)
    return args[0]->clone();

  NumberObj* ans = dynamic_cast<NumberObj*>(args[0]->clone());
  try{
    for(int i = 1; i < args.size(); ++i){
      converter.addObj(ans, dynamic_cast<NumberObj*>(args[i]));
    }
  }catch(std::string& s){
    delete ans;
    throw s;
  }
  return ans;
}
