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
  // Lambda éÆÇçÏê¨Çµï‘Ç∑
  Object* execute(ListObj& parameter, Env* e);
};

#endif
