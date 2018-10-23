#ifndef PROC_OBJECT
#define PROC_OBJECT

#include"../../Environment.hpp"
#include"../ListObj.hpp"
#include<string>

// ���s�\�Ȋ֐���\���N���X
class ProcObj : public Object{
protected:
  std::string name;
public:
  ProcObj() : Object(PROC_OBJ) {}
  ProcObj(std::string name) : name(name), Object(PROC_OBJ) {}
  virtual ~ProcObj(){};
  Object* eval(Env* env){ return clone(); }
  // �֐��̎��s�Aparameter �������Aenv �͎��s��
  virtual Object* execute(ListObj& parameter, Env* env) = 0;
};

#endif