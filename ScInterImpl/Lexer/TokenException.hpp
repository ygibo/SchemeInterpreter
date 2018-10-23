#ifndef TOKEN_EXCEPTION
#define TOKEN_EXCEPTION

#include<iostream>
#include<fstream>
#include<string>

class TokenException{
private:
  int row, colmn;
  std::string message;
  std::string code;
public:
  TokenException(){}
  TokenException(int row, int colmn, std::string message, std::string code)
    : row(row), colmn(colmn), message(message), code(code) {}
  void showErrorMessage(std::ostream& ofs){
    ofs << "Token Error (" << row << ", " << colmn << "):"
	<< message << std::endl;
    ofs << code << std::endl;
  }
};

#endif
