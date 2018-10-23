#include"EvalException.hpp"
#include"EvalErrorMessage.hpp"

class InvalidParamException : public EvalException{
public:
  InvalidParamException(){}
};
