#ifndef LIST_PROCEDURE_OBJECT
#define LIST_PROCEDURE_OBJECT

#include<string>
#include<iostream>
#include"../../Object.hpp"
#include"../../ListObj.hpp"
#include"../ProcObj.hpp"
#include"../../../Environment.hpp"

class ListProcObj : public ProcObj{
public:
  ListProcObj() : ProcObj() {}
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  // リスト式を作成し返す
  Object* execute(ListObj& param_list, Env* env);
};

#endif
