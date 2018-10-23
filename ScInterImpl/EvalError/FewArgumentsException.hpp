#include"EvalException.hpp"
#include"EvalErrorMessage.hpp"

class FewArgumentsException : public EvalException{
public:
  FewArgumentsException(){}
};
