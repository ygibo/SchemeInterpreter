#ifndef LAMBDA_FACTORY
#define LAMBDA_FACTORY

#include<vector>
#include<string>
#include"../../../Environment.hpp"
#include"../../../Lexer/Lexer.hpp"
#include"../ProcObj.hpp"

class LambdaProcObj : public ProcObj{
public:
  LambdaProcObj() : ProcObj(){}
  ~LambdaProcObj() {}
  std::string print();
  Object* clone();
  // Lambda 式を作成し返す
  Object* execute(ListObj& parameter, Env* e);
};

#endif
