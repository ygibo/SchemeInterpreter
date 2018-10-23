#ifndef SET_OBJECT
#define SET_OBJECT

#include<string>
#include"../../../Object.hpp"
#include"../../../../Environment.hpp"
#include"../../../../Lexer/Lexer.hpp"
#include"../../../SymbolObj.hpp"

class SetObj : public Object{
private:
  std::string symbolName;
  Object* val;
public:
  SetObj() : val(NULL), Object(SYNTAX_OBJ) {}
  SetObj(std::string symbolName, Object* val) :
    symbolName(symbolName), val(val),  Object(SYNTAX_OBJ) {}
  ~SetObj();
  void set(Lexer& l);
  void setSymbolName(std::string name);
  void setValue(Object* obj);
  Object* eval(Env* env);
  std::string print();
  Object* clone();
};


#endif
  
