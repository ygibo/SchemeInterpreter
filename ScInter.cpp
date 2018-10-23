#include"ScInter.hpp"
#include"ScInterImpl/Lexer/Lexer.hpp"
#include"ScInterImpl/Lexer/TokenException.hpp"
#include"ScInterImpl/Parser/Parser.hpp"
#include"ScInterImpl/Environment.hpp"
#include"ScInterImpl/SchemeObjects/Object.hpp"
#include"ScInterImpl/SchemeObjects/SymbolObj.hpp"
#include"ScInterImpl/SchemeObjects/BoolObj.hpp"
#include"ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/DefineProcObj.hpp"
#include"ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/LambdaProcObj.hpp"
#include"ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/SetProcObj.hpp"
#include"ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/PairProcObj.hpp"
#include"ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/QuoteProcObj.hpp"
#include"ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/ListProcObj.hpp"
#include"ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/PremitiveObj.hpp"
#include"ScInterImpl/SyntaxError/SyntaxErrorException.hpp"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cassert>

bool ScInter::isEnd(){
  return isErrorOccur || lex.isEnd();
}

void setGlovalFunc(Env* env){
  // 環境へキーワードに、対応する構文を実行するオブジェクトを設定する
  env->setSymbol("define", new DefineProcObj());
  env->setSymbol("lambda", new LambdaProcObj());
  env->setSymbol("set!", new SetProcObj());
  env->setSymbol("cons", new PairProcObj());
  env->setSymbol("quote", new QuoteProcObj());
  env->setSymbol("list", new ListProcObj());
  env->setSymbol("+", new PremitiveObj("+"));
  env->setSymbol("-", new PremitiveObj("-"));
  env->setSymbol("/", new PremitiveObj("/"));
  env->setSymbol("*", new PremitiveObj("*"));
  env->setSymbol("car", new PremitiveObj("car"));
  env->setSymbol("cdr", new PremitiveObj("cdr"));
  env->setSymbol("#t", new BoolObj(true));
  env->setSymbol("#f", new BoolObj(false));
}

ScInter::ScInter(std::string file_name)
  : lex(file_name), file_name(file_name), isErrorOccur(false) {
}

void ScInter::init(){
  try{
    // 字句解析を行いトークンを設定する
    lex.scan();
  }catch(TokenException& token_error){
    token_error.showErrorMessage(std::cerr);
    return;
  }catch(std::string s){
    std::cerr << s << std::endl;
  }catch(...){
    std::cerr << "Catch Error" << std::endl;
    return;
  }
  env = Env();
  // 環境へdefine や list 等の構文を設定する
  setGlovalFunc(&env);
}

std::string ScInter::executeOneExp(){
  if(isErrorOccur)
    return std::string("Error: ScInter is Stopped.");
  Object* parse_obj = NULL;
  try{
    // syntax tree を作る
    parse_obj = Parser::getSyntaxTree(lex);
  }catch(std::string str){
    isErrorOccur = true;
    std::cerr << "Parse Error: " << str << std::endl;
    return "Error";
  }

  assert(parse_obj != NULL && "parse obj is null");
  Object* ret = NULL;
  
  try{
    // 実行する
    ret = parse_obj->eval(&env);
  }catch(std::string s){
    isErrorOccur = true;
    std::cerr << "Eval Error: " << s << std::endl;
    return "Error";
  }
  std::string ret_str;
  if(ret != NULL){
    // 実行した結果のオブジェクトを印字する
    ret_str = ret->print();
    delete ret;
  }
  delete parse_obj;
  return ret_str;
}


