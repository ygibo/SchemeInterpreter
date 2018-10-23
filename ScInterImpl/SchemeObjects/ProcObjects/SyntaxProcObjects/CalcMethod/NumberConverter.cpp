#include"NumberConverter.hpp"
#include"../../../SelfEvalObjects/NumberObjects/NumberObj.hpp"
#include"../../../SelfEvalObjects/NumberObjects/IntegerObj.hpp"  
#include<iostream>

bool NumberConverter::isNumberObj(std::vector<Object*>& args){
  for(int i = 0; i < args.size(); ++i){
    if(args[i]->getType() != NUMBER_OBJ)
      return false;
  }
  return true;
}

void NumberConverter::addObj(NumberObj* added_obj, NumberObj* adding){
  if(added_obj->getNumberType() == INTEGER_TYPE &&
     adding->getNumberType() == INTEGER_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    int ans = int_added_obj->getVal() + int_adding->getVal();
    dynamic_cast<IntegerObj*>(added_obj)->set(ans);
  }/*else if(added_obj->getNumberType() == DOUBLE_TYPE &&
	   adding->getNumberType() == DOUBLE_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    ans = static_cast<NumberObj*>(new IntegerObj(int_added_obj->getVal() +
						 int_adding->getVal()));
   */
}
				  
void NumberConverter::minus(NumberObj* added_obj, NumberObj* adding){
  if(added_obj->getNumberType() == INTEGER_TYPE &&
     adding->getNumberType() == INTEGER_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    int ans = int_added_obj->getVal() - int_adding->getVal();
    dynamic_cast<IntegerObj*>(added_obj)->set(ans);
  }/*else if(added_obj->getNumberType() == DOUBLE_TYPE &&
	   adding->getNumberType() == DOUBLE_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    ans = static_cast<NumberObj*>(new IntegerObj(int_added_obj->getVal() +
						 int_adding->getVal()));
   */
}
				  
void NumberConverter::div(NumberObj* added_obj, NumberObj* adding){
  if(added_obj->getNumberType() == INTEGER_TYPE &&
     adding->getNumberType() == INTEGER_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    if(int_adding->getVal() == 0)
      throw std::string("devide 0 error");
    int ans = int_added_obj->getVal() / int_adding->getVal();
    dynamic_cast<IntegerObj*>(added_obj)->set(ans);
  }/*else if(added_obj->getNumberType() == DOUBLE_TYPE &&
	   adding->getNumberType() == DOUBLE_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    ans = static_cast<NumberObj*>(new IntegerObj(int_added_obj->getVal() +
						 int_adding->getVal()));
   */
}

void NumberConverter::mul(NumberObj* added_obj, NumberObj* adding){
  if(added_obj->getNumberType() == INTEGER_TYPE &&
     adding->getNumberType() == INTEGER_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    int ans = int_added_obj->getVal() * int_adding->getVal();
    dynamic_cast<IntegerObj*>(added_obj)->set(ans);
  }/*else if(added_obj->getNumberType() == DOUBLE_TYPE &&
	   adding->getNumberType() == DOUBLE_TYPE){
    IntegerObj* int_added_obj = dynamic_cast<IntegerObj*>(added_obj);
    IntegerObj* int_adding = dynamic_cast<IntegerObj*>(adding);
    ans = static_cast<NumberObj*>(new IntegerObj(int_added_obj->getVal() +
						 int_adding->getVal()));
   */
}
				  

