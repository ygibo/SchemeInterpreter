#ifndef SCHEME_PARSER
#define SCHEME_PARSER

#include"../SchemeObjects/Object.hpp"
#include"../Lexer/Lexer.hpp"

class Parser{
public:
  // ���X�g�Ǝ��ȕ]�����A�V���[�v���A�V���{�����\����͂��A�\����͖؂�Ԃ�
  static Object* getSyntaxTree(Lexer& l);
};

#endif