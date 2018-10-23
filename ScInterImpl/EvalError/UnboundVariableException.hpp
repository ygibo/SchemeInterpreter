#ifndef UNBOUND_VARIABLE_EXCEPTION
#define UNBOUND_VARIABLE_EXCEPTION

#include<string>
#include"EvalException.hpp"

class UnboundVariableException : public EvalException {
public:
  UnboundVariableException() : EvalException(0, 0, "", "") {}
  UnboundVariableException(int row, int colmn,
			   std::string code, std::string message) :
    EvalException(row, colmn, code, message) {}
  void show(std::ostream& os){
    os << "Unbound Variable Error:" << row << ":" << colmn << ": "
       << message << std::endl;
    os << code << std::endl;
  }
};

#endif
