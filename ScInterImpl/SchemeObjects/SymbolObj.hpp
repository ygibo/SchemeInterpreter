#ifndef SYMBOL_OBJECT
#define SYMBOL_OBJECT

#include<string>
#include"Object.hpp"
#include"../Environment.hpp"
#include"../Lexer/Lexer.hpp"

class SymbolObj : public Object{
private:
  std::string id;
public:
  SymbolObj() : Object(SYMBOL_OBJ) {}
  SymbolObj(std::string id) : id(id), Object(SYMBOL_OBJ) {}
  ~SymbolObj() {}
  
  void set(std::string name);
  std::string getId();
   Object* eval(Env* e);
  std::string print();
  Object* clone();
};

#endif
