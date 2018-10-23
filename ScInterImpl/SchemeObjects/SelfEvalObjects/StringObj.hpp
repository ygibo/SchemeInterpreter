#ifndef STRING_OBJECT
#define STRING_OBJECT

#include"../Object.hpp"
#include"../../Environment.hpp"
#include"../../Lexer/Lexer.hpp"
#include<string>

class StringObj : public Object{
private:
  std::string str;
public:
  StringObj() : Object(STRING_OBJ) {}
  StringObj(std::string str) :
    str(str), Object(STRING_OBJ) {}
  ~StringObj() {}
  void set(std::string s);
  std::string getString();
  Object* eval(Env* env);
  std::string print();
  Object* clone();
};
  
#endif
