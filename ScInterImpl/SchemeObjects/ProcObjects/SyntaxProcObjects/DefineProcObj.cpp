//#define DEBUG
#include"DefineProcObj.hpp"
#include"SyntaxObjects/DefineObj.hpp"
#include"../LambdaObj.hpp"
#include"../../SymbolObj.hpp"

Object* DefineProcObj::execute(ListObj& param_list, Env* env){
#ifdef DEBUG
  std::cout << "execute defineProcObj" << std::endl;
  std::cout << param_list.print() << std::endl;
#endif
  DefineObj define_obj;
  define_obj.setFromListObj(param_list);
#ifdef DEBUG
  std::cout << "eval created define statement" << std::endl;
  std::cout << define_obj.print() << std::endl;
#endif
  define_obj.eval(env);
#ifdef DEBUG
  std::cout << "eval end" << std::endl;
#endif
  return NULL;
}

  
Object* DefineProcObj::eval(Env* env){
  return clone();
}

std::string DefineProcObj::print(){
  return "(#define factory)";
}

Object* DefineProcObj::clone(){
  return new DefineProcObj();
}

