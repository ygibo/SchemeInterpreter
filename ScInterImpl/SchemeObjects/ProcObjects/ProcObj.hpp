#ifndef PROC_OBJECT
#define PROC_OBJECT

#include"../../Environment.hpp"
#include"../ListObj.hpp"
#include<string>

// 実行可能な関数を表すクラス
class ProcObj : public Object{
protected:
  std::string name;
public:
  ProcObj() : Object(PROC_OBJ) {}
  ProcObj(std::string name) : name(name), Object(PROC_OBJ) {}
  virtual ~ProcObj(){};
  Object* eval(Env* env){ return clone(); }
  // 関数の実行、parameter が引数、env は実行環境
  virtual Object* execute(ListObj& parameter, Env* env) = 0;
};

#endif
