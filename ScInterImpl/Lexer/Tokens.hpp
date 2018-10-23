#ifndef SCHEME_TOKENS
#define SCHEME_TOKENS

#include<string>
#include<sstream>
#include<iostream>

enum Type{
  NUM, DOUBLE, LEFT_PARAM, RIGHT_PARAM,
  WORD, DOT, QUOTE, STRING, RATIONAL, SHARP,
  BACK_SLASH, UNKNOWN, NONE
};

class Token{
private:
  int startColmn, endColmn;
  int startRow, endRow;
public:
  Token(int startRow, int startColmn,
	int endRow, int endColmn)
    : startRow(startRow), startColmn(startColmn),
      endRow(endRow), endColmn(endColmn) {}
  virtual Type getType() = 0;
  virtual std::string getCode() = 0;
  int getStartRow(){ return startRow; }
  int getStartColmn(){ return startColmn; }
  int getEndRow(){ return endRow; }
  int getEndColmn(){ return endColmn; }
};

class LeftParam : public Token{
 public:
  LeftParam(int startRow, int startColmn, int endRow, int endColmn)
    : Token(startRow, startColmn, endRow, endColmn) {}
  Type getType(){ return LEFT_PARAM; }
  std::string getCode(){ return "("; }
};

class RightParam : public Token{
public:
  RightParam(int startRow, int startColmn, int endRow, int endColmn)
    : Token(startRow, startColmn, endRow, endColmn) {}
  Type getType(){ return RIGHT_PARAM; }
  std::string getCode(){ return ")"; }
};

class Sharp : public Token{
public:
  Sharp(int startRow, int startColmn, int endRow, int endColmn)
    : Token(startRow, startColmn, endRow, endColmn ) {}
  Type getType(){ return SHARP; }
  std::string getCode(){ return "#"; }
};

class BackSlash : public Token{
public:
  BackSlash(int startRow, int startColmn, int endRow, int endColmn)
    : Token(startRow, startColmn, endRow, endColmn) {}
  Type getType(){ return BACK_SLASH; }
  std::string getCode(){ return "\\"; }
};

class Word : public Token{
private:
  std::string name;
public:
  Type getType(){ return WORD; }
  Word(int startRow, int startColmn, int endRow, int endColmn, std::string name)
    : name(name), Token(startRow, startColmn, endRow, endColmn) {}
  std::string getName(){ return name; }
  std::string getCode(){ return name; }
};

class Unknown : public Token{
private:
  std::string name;
public:
  Type getType(){ return WORD; }
  Unknown(int startRow, int startColmn,
	  int endRow, int endColmn, std::string name)
    : name(name), Token(startRow, startColmn, endRow, endColmn) {}
  std::string getName(){ return name; }
  std::string getCode(){ return name; }
};

class Num : public Token{
private:
  int num;
public:
  Type getType(){ return NUM; }
  Num(int startRow, int startColmn, int endRow, int endColmn, int n) :
    num(n), Token(startRow, startColmn, endRow, endColmn) {}
  int getVal(){ return num; }
  std::string getCode(){
    std::stringstream os;
    os << num;
    return os.str();
  }
};

class Double : public Token{
private:
  double num;
public:
  Type getType(){ return DOUBLE; }
  Double(int startRow, int startColmn, int endRow, int endColmn, double d) :
    num(d), Token(startRow, startColmn, endRow, endColmn) {}
  double getVal(){ return num; }
  std::string getCode(){
    std::stringstream os;
    os << num;
    return os.str();
  }
};

class Dot : public Token{
public:
  Type getType(){ return DOT; }
  Dot(int startRow, int startColmn, int endRow, int endColmn)
    : Token(startRow, startColmn, endRow, endColmn) {}
  std::string getCode(){
    return ".";
  }
};

class Quote : public Token{
public:
  Type getType(){ return QUOTE; }
  Quote(int startRow, int startColmn, int endRow, int endColmn)
    : Token(startRow, startColmn, endRow, endColmn) {}
  std::string getCode(){
    return "\'";
  }
};

class ScString : public Token{
private:
  std::string str;
public:
  Type getType(){ return STRING; }
  ScString(int startRow, int startColmn,
	   int endRow, int endColmn,
	   std::string str)
    : Token(startRow, startColmn, endRow, endColmn), str(str){}
  
  std::string getString(){ return str; }
  std::string getCode(){
    return "\"" + str + "\"";
  }
};

#endif
