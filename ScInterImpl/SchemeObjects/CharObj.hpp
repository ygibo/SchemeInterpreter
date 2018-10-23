#ifndef CHAR_OBJECT
#define CHAR_OBJECT

#include<string>
#include"Object.hpp"
#include"../Environment.hpp"
#include"../Lexer/Lexer.hpp"

class CharObj : public Object{
private:
  char c;
public:
  CharObj(char c) : c(c), Object(CHAR_OBJ) {};
  ~CharObj() {};
  Object* eval(Env* env);
  std::string print();
  Object* clone();
};

#endif
