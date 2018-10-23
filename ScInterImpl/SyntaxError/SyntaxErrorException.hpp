#ifndef SYNTAX_ERROR_EXCEPTION
#define SYNTAX_ERROR_EXCEPTION

#include<string>
#include<iostream>
#include<fstream>

class SyntaxErrorException{
private:
  int row;
  int colmn;
  std::string message;
  std::string code;
public:
  SyntaxErrorException(int row, int colmn,
		       std::string message,
		       std::string code) :
    row(row), colmn(colmn), message(message), code(code) {}
  void show(std::ostream& os){
    os << "Syntax Error:" << row << ":" << colmn << ": "
       << message << std::endl;
    os << code << std::endl;
  }
  void setRow(int r){ row = r; }
  void setColmn(int c){ colmn = c; }
  void setCode(std::string c){ code = c; }
};

#endif
