#ifndef SCHEME_OBJECT
#define SCHEME_OBJECT

#include"../Environment.hpp"

enum ObjectType{
  NUMBER_OBJ = 1, STRING_OBJ = 2,
  PAIR_OBJ, SYMBOL_OBJ, QUOTE_OBJ,
  LIST_OBJ, PROC_OBJ, SYNTAX_OBJ,
  BOOL_OBJ, CHAR_OBJ, VECTOR_OBJ
};

class Env;

class Object{
private:
  int startRow;
  int startColmn;
  int endRow;
  int endColmn;
  ObjectType type;
public:
  Object(ObjectType type) : type(type) {}
  virtual ~Object() {}
  ObjectType getType() { return type; }
  virtual Object* eval(Env* env) = 0;
  virtual std::string print() = 0;
  virtual Object* clone() = 0;
  void setStart(int row, int colmn){
    startRow = row;
    startColmn = colmn;
  }
  void setEnd(int row, int colmn){
    endRow = row;
    endColmn = colmn;
  }
  int getStartRow(){ return startRow; }
  int getStartColmn(){ return startColmn; }
  int getEndRow(){ return endRow; }
  int getEndColmn(){ return endColmn; }
};

#endif
