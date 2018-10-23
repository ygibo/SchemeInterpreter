#ifndef QUOTE_PROC_OBJECT
#define QUOTE_PROC_OBJECT

#include<string>
#include<iostream>
#include"../../Object.hpp"
#include"../ProcObj.hpp"
#include"../../../Environment.hpp"
#include"../../QuoteObj.hpp"

class QuoteProcObj : public ProcObj{
public:
  QuoteProcObj() : ProcObj() {}
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  Object* execute(ListObj& param_list, Env* env);
};

#endif
