OBJGROUP=Lexer.o Environment.o IntegerObj.o StringObj.o SymbolObj.o SetObj.o SetProcObj.o LambdaObj.o LambdaProcObj.o  DefineObj.o DefineProcObj.o ListObj.o PairObj.o PairProcObj.o PremitiveObj.o PlusMethod.o MinusMethod.o DivMethod.o MulMethod.o NumberConverter.o CarMethod.o CdrMethod.o QuoteObj.o QuoteProcObj.o ListProcObj.o Parser.o ScInter.o BoolObj.o CharObj.o ObjectFactory.o

LEXER_PATH = ScInterImpl/Lexer/
OBJ_PATH = ScInterImpl/SchemeObjects/
NUMBER_PATH = ScInterImpl/SchemeObjects/SelfEvalObjects/NumberObjects/
SYNTAX_PROC_PATH = ScInterImpl/SchemeObjects/ProcObjects/SyntaxProcObjects/
CALC_METHOD_PATH = $(SYNTAX_PROC_PATH)CalcMethod/
OBJECT_PATH = objects/
FACTORY_PATH = ScInterImpl/ObjectFactory/

main: main.cpp $(OBJGROUP)
	g++ -g3 -o main main.cpp $(OBJECT_PATH)*.o
ScInter.o: ScInter.cpp
	g++ -c ScInter.cpp -o $(OBJECT_PATH)ScInter.o
Parser.o: ScInterImpl/Parser/Parser.cpp
	g++ -c ScInterImpl/Parser/Parser.cpp -o $(OBJECT_PATH)Parser.o
Lexer.o: $(LEXER_PATH)Lexer.cpp Parser.o
	g++ -c $(LEXER_PATH)Lexer.cpp -o $(OBJECT_PATH)lexer.o
Environment.o: ScInterImpl/Environment.cpp
	g++ -c ScInterImpl/Environment.cpp -o $(OBJECT_PATH)Environment.o
ObjectFactory.o: $(FACTORY_PATH)ObjectFactory.cpp
	g++ -c $(FACTORY_PATH)ObjectFactory.cpp -o $(OBJECT_PATH)ObjectFactory.o
IntegerObj.o: $(NUMBER_PATH)IntegerObj.cpp
	g++ -c $(NUMBER_PATH)IntegerObj.cpp -o $(OBJECT_PATH)IntegerObj.o
StringObj.o: $(OBJ_PATH)SelfEvalObjects/StringObj.cpp
	g++ -c $(OBJ_PATH)SelfEvalObjects/StringObj.cpp -o $(OBJECT_PATH)StringObj.o
SymbolObj.o: $(OBJ_PATH)SymbolObj.cpp
	g++ -c $(OBJ_PATH)SymbolObj.cpp -o $(OBJECT_PATH)SymbolObj.o
CharObj.o: $(OBJ_PATH)CharObj.cpp
	g++ -c $(OBJ_PATH)CharObj.cpp -o $(OBJECT_PATH)CharObj.o
BoolObj.o: $(OBJ_PATH)BoolObj.cpp
	g++ -c $(OBJ_PATH)BoolObj.cpp -o $(OBJECT_PATH)BoolObj.o
QuoteObj.o: $(OBJ_PATH)QuoteObj.cpp
	g++ -c $(OBJ_PATH)QuoteObj.cpp -o $(OBJECT_PATH)QuoteObj.o
QuoteProcObj.o: $(SYNTAX_PROC_PATH)QuoteProcObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)QuoteProcObj.cpp -o $(OBJECT_PATH)QuoteProcObj.o
SetObj.o: $(SYNTAX_PROC_PATH)SyntaxObjects/SetObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)SyntaxObjects/SetObj.cpp -o $(OBJECT_PATH)SetObj.o
SetProcObj.o: $(SYNTAX_PROC_PATH)SetProcObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)SetProcObj.cpp -o $(OBJECT_PATH)SetProcObj.o
LambdaObj.o: $(OBJ_PATH)ProcObjects/LambdaObj.cpp
	g++ -c $(OBJ_PATH)ProcObjects/LambdaObj.cpp -o $(OBJECT_PATH)LambdaObj.o
LambdaProcObj.o: $(SYNTAX_PROC_PATH)LambdaProcObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)LambdaProcObj.cpp -o $(OBJECT_PATH)LambdaProcObj.o
DefineObj.o: $(SYNTAX_PROC_PATH)SyntaxObjects/DefineObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)SyntaxObjects/DefineObj.cpp -o $(OBJECT_PATH)DefineObj.o
DefineProcObj.o: $(SYNTAX_PROC_PATH)DefineProcObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)DefineProcObj.cpp -o $(OBJECT_PATH)DefineProcObj.o
ListObj.o: $(OBJ_PATH)ListObj.cpp
	g++ -c $(OBJ_PATH)ListObj.cpp -o $(OBJECT_PATH)ListObj.o
PairObj.o: $(OBJ_PATH)PairObj.cpp
	g++ -c $(OBJ_PATH)PairObj.cpp -o $(OBJECT_PATH)PairObj.o
PairProcObj.o: $(SYNTAX_PROC_PATH)PairProcObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)PairProcObj.cpp -o $(OBJECT_PATH)PairProcObj.o
ListProcObj.o: $(SYNTAX_PROC_PATH)ListProcObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)ListProcObj.cpp -o $(OBJECT_PATH)ListProcObj.o
PremitiveObj.o: $(SYNTAX_PROC_PATH)PremitiveObj.cpp
	g++ -c $(SYNTAX_PROC_PATH)PremitiveObj.cpp -o $(OBJECT_PATH)PremitiveObj.o
PlusMethod.o: $(CALC_METHOD_PATH)PlusMethod.cpp
	g++ -c $(CALC_METHOD_PATH)PlusMethod.cpp -o $(OBJECT_PATH)PlusMethod.o
MinusMethod.o: $(CALC_METHOD_PATH)MinusMethod.cpp
	g++ -c $(CALC_METHOD_PATH)MinusMethod.cpp -o $(OBJECT_PATH)MinusMethod.o
DivMethod.o: $(CALC_METHOD_PATH)DivMethod.cpp
	g++ -c $(CALC_METHOD_PATH)DivMethod.cpp -o $(OBJECT_PATH)DivMethod.o
MulMethod.o: $(CALC_METHOD_PATH)MulMethod.cpp
	g++ -c $(CALC_METHOD_PATH)MulMethod.cpp -o $(OBJECT_PATH)MulMethod.o
CarMethod.o: $(CALC_METHOD_PATH)CarMethod.cpp
	g++ -c $(CALC_METHOD_PATH)CarMethod.cpp -o $(OBJECT_PATH)CarMethod.o
CdrMethod.o: $(CALC_METHOD_PATH)CdrMethod.cpp
	g++ -c $(CALC_METHOD_PATH)CdrMethod.cpp -o $(OBJECT_PATH)CdrMethod.o

NumberConverter.o:
	g++ -c $(CALC_METHOD_PATH)NumberConverter.cpp -o $(OBJECT_PATH)NumberConverter.o



clean:
	rm main $(OBJECT_PATH)$(OBJGROUP)
