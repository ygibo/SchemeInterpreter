#ifndef PAIR_FACTORY
#define PAIR_FACTORY

#include<string>
#include<iostream>
#include"../../Object.hpp"
#include"../../ListObj.hpp"
#include"../ProcObj.hpp"
#include"../../../Environment.hpp"

class PairProcObj : public ProcObj{
public:
  PairProcObj() : ProcObj() {}
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  Object* execute(ListObj& param_list, Env* env);
};

#endif
