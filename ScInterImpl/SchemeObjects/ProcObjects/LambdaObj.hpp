#ifndef LAMBDA_OBJECT
#define LAMBDA_OBJECT

#include<vector>
#include<string>
#include"../../Environment.hpp"
#include"../../Lexer/Lexer.hpp"
#include"ProcObj.hpp"
#include"../ListObj.hpp"

// Lambda 式を表すオブジェクト
class LambdaObj : public ProcObj{
private:
  std::vector<std::string> paramName; // パラメータ名
  std::vector<Object*> body; // lambda 式の body
public:
  LambdaObj() : ProcObj("lambda") {}
  ~LambdaObj();
  // パラメータを追加
  void addParam(std::string name);
  // lambda 式の body を追加
  void addBody(Object* obj);
  Object* clone();
  // lambda 式への引数と環境を取って実行する
  Object* execute(ListObj& paramList, Env* e);
  std::string print();
};

#endif
