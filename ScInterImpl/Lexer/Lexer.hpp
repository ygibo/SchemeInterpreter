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
  std::string file_name; // ���͂̐ݒ�
  std::vector<std::vector<Token*> > table;
  int currentRow; // ���ݑ������̍s�ԍ�
  int currentColmn; // ���ݑ������̗�ԍ�
 public:
  Lexer(){}
  Lexer(std::string file_name) : file_name(file_name) {}
  
  ~Lexer();

  // ���݂̃g�[�N���̃^�C�v�𓾂�
  Type getKindOfCurrentType();
  // ���݂̃g�[�N����Ԃ�
  Token* getToken();
  // ���̃g�[�N����Ԃ�
  Token* getNextToken();
  // ���̃g�[�N�����w��
  void next();
  // �g�[�N�����Ō�܂ő��삵�����H
  int isEnd();
  // ���ݑ������̍s�ԍ���Ԃ�
  int getLineNum();
  // ���͂���̃R�[�h���X�L�������g�[�N���Ƃ��ĕێ�����
  void scan();
  // ���ݕێ����Ă���g�[�N�������ׂĕ\��
  void show();
  // ���݂̍s�̃R�[�h�𓾂�
  std::string getCode();
  // lineNum �s�ڂ̃R�[�h��Ԃ�
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