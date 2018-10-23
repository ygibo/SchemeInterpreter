#ifndef DEFINE_OBJECT
#define DEFINE_OBJECT

#include<string>
#include<iostream>
#include"../../../Object.hpp"
#include"../../ProcObj.hpp"
#include"../../../../Environment.hpp"
#include"../../../../Lexer/Lexer.hpp"

class DefineObj : public Object{
private:
  std::string id;
  Object* obj;
public:
  DefineObj() : obj(NULL), Object(SYNTAX_OBJ) {}
  ~DefineObj();

  void set(Lexer& lex);
  void setId(std::string name);
  void setId(Object* id_obj);
  void setObject(Object* object);
  void setFromListObj(ListObj& params);
  Object* eval(Env* env);
  std::string print();
  Object* clone();
};

#endif
