#include"EvalException.hpp"
#include"EvalErrorMessage.hpp"

class TooManyArgumentsException : public EvalException{
public:
  TooManyArgumentsException(){}
};
