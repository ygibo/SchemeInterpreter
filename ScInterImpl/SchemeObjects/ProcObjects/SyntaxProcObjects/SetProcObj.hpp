#ifndef SET_FACTORY
#define SET_FACTORY
#include"../../Object.hpp"
#include"../ProcObj.hpp"
#include"../../ListObj.hpp"
#include"../../../Environment.hpp"

class SetProcObj : public ProcObj{
public:
  SetProcObj() : ProcObj() {}
  Object* eval(Env* env);
  std::string print();
  Object* clone();
  Object* execute(ListObj& param_list, Env* env);
};

#endif
