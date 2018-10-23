#ifndef SCHEME_LEXER
#define SCHEME_LEXER

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cctype>
#include"Tokens.hpp"
#include"TokenException.hpp"

class Lexer{
 private:
  std::string file_name; // 入力の設定
  std::vector<std::vector<Token*> > table;
  int currentRow; // 現在走査中の行番号
  int currentColmn; // 現在走査中の列番号
 public:
  Lexer(){}
  Lexer(std::string file_name) : file_name(file_name) {}
  
  ~Lexer();

  // 現在のトークンのタイプを得る
  Type getKindOfCurrentType();
  // 現在のトークンを返す
  Token* getToken();
  // 次のトークンを返す
  Token* getNextToken();
  // 次のトークンを指す
  void next();
  // トークンを最後まで操作したか？
  int isEnd();
  // 現在走査中の行番号を返す
  int getLineNum();
  // 入力からのコードをスキャンしトークンとして保持する
  void scan();
  // 現在保持しているトークンをすべて表示
  void show();
  // 現在の行のコードを得る
  std::string getCode();
  // lineNum 行目のコードを返す
  std::string getCode(int lineNum);
private:
  void setIndexAfterSkippingSpace(int& index,const std::string str);
  bool isDelimiter(int& index, const std::string str);
  int getNumber(int& index, const std::string str);
  void setNumber(int& index, const std::string str);
  double getNumAfterDecimalPoint(int& index,const std::string str);
  double getDecimalNumAfterDecimalPoint(int num);
  int getDigit(const char c);
  void setLeftParam(int& index, const std::string str);
  void setRightParam(int& index, const std::string str);
  void setWord(int& index, const std::string str);
  void setDot(int& index, const std::string str);
  void setQuote(int& index, const std::string str);
  void setSharp(int& index, const std::string str);
  std::string getString(int& index, const std::string str);
  void setString(int& index, const std::string str,
		 const std::string sc_string,
		 int startRow, int startColmn,
		 int endRow, int endColmn);
  bool isExtendedIdentifier(char c);
  void skipEmptyRow();
  void setSpace(std::string& string, int num);
  std::string getStringUpToFirstDelimiter(std::string& str,
					  char delimiter);
  void setUnknown(int& index, const std::string str);
  void setBackSlash(int& index,std::string str);
  void skipEmptyRow(int& row, int& colmn);
  void next(int& row, int& colmn);
};

#endif
