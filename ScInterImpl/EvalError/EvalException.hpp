#ifndef EVAL_EXCEPTION
#define EVAL_EXCEPTION

#include<iostream>
#include<string>

class EvalException{
protected:
  int row, colmn;
  std::string message;
public:
  EvalException(){}
  EvalException(int row, int colmn,
		std::string message) :
    row(row), colmn(colmn), message(message) {}
  void show(std::ostream& os){
    os << "Evaluation Error: " << row << ":" << colmn
       << ": " << message << std::endl;
  }
  int setRow(int r){ row = r; }
  int setColmn(int c){ colmn = c; }
  int setMessage(std::string str){ message = str; }
  int addMessage(std::string str){ message += str; }
  int getRow(){ return row; }
  int getColmn(){ return colmn; }
};

#endif
