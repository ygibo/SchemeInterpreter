#ifndef DEFINE_FACTORY
#define DEFINE_FACTORY

#include<string>
#include<iostream>
#include"../../Object.hpp"
#include"../../ListObj.hpp"
#include"../ProcObj.hpp"
#include"../../../Environment.hpp"

class DefineProcObj : public ProcObj{
public:
  DefineProcObj() : ProcObj() {}
  // 何もしない
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  // define 文へのパラメータを渡し、define 文を実行する
  Object* execute(ListObj& param_list, Env* env);
};

#endif
