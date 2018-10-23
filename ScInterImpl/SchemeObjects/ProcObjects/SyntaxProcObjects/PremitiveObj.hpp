#ifndef PREMITIVE_OBJECT
#define PREMITIVE_OBJECT

#include<vector>
#include<string>
#include"../../../Environment.hpp"
#include"../../../Lexer/Lexer.hpp"
#include"../../Object.hpp"
#include"../ProcObj.hpp"
#include"../../ListObj.hpp"
#include"CalcMethod/CalcMethod.hpp"


class PremitiveObj : public ProcObj{
private:
  CalcMethod* method;
public:
  PremitiveObj() : method(NULL), ProcObj() {}
  PremitiveObj(std::string methodName);
  ~PremitiveObj();
  void set(Lexer& l);
  Object* eval(Env* e);
  std::string print();
  Object* clone();
  Object* execute(ListObj& obj, Env* e);
  void setMethod(std::string methodName);
};
  
#endif
