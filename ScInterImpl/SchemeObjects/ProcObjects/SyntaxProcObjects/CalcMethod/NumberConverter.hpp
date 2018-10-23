#ifndef NUMBER_CONVERTER
#define NUMBER_CONVERTER

#include<vector>
#include"../../../SelfEvalObjects/NumberObjects/NumberObj.hpp"

class NumberConverter{
public:
  bool isNumberObj(std::vector<Object*>& args);
  void addObj(NumberObj* added_obj,NumberObj* adding);
  void minus(NumberObj* added_obj, NumberObj* adding);
  void mul(NumberObj* added_obj, NumberObj* adding);
  void div(NumberObj* added_obj, NumberObj* adding);
};

#endif
