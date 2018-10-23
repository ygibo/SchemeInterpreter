#include"Lexer.hpp"
#include"ErrorMessage.hpp"
#include"TokenException.hpp"

Lexer::~Lexer(){
  // �쐬���� Token ��j������
  for(int row = 0; row < table.size(); row++){
    for(int colmn = 0; colmn < table[row].size(); ++colmn){
      if(table[row][colmn] != NULL)
	delete table[row][colmn];
    }
  }
}

// �g�[�N���̃^�C�v�𓾂�
Type Lexer::getKindOfCurrentType(){
  if(isEnd())
    return NONE;
  return table[currentRow][currentColmn]->getType();
}


void Lexer::skipEmptyRow(int& row, int& colmn){
  while(row < table.size() && table[row].size() == 0)
    ++row;
  colmn = 0;
}

// ��s���΂�
void Lexer::skipEmptyRow(){
  skipEmptyRow(currentRow, currentColmn);
}

void Lexer::next(int& row, int& colmn){
  if(table[row].size() == 0){
    // ��s�Ȃ��΂�
    skipEmptyRow(row, colmn);
  }else{
    ++colmn;
    if(colmn >= table[row].size()){
      // ���̍s�̏I���ɂȂ�����,���̋�s�łȂ��s�֍s��
      ++row;
      skipEmptyRow(row, colmn);
    }
  }
}
  
// ���̃g�[�N���֍s��
void Lexer::next(){
  next(currentRow, currentColmn);
}

// ���ׂẴg�[�N���𑖍��������H
int Lexer::isEnd(){
    return currentRow >= table.size();
}

// ���ݑ������̍s�ԍ��𓾂�
int Lexer::getLineNum(){
  return currentRow;
}

// ���ݑ������̃g�[�N����Ԃ�
Token* Lexer::getToken(){
  return table[currentRow][currentColmn];
}

Token* Lexer::getNextToken(){
  int nextRow = currentRow;
  int nextColmn = currentColmn;
  next(nextRow, nextColmn);
  if(nextRow >= table.size())
    return NULL;
  return table[nextRow][nextColmn];
}

// �X�y�[�X���΂�
void Lexer::setIndexAfterSkippingSpace(int& index,const std::string str){
  while(str[index] == ' ' || str[index] == '\t')
    ++index;
}

int Lexer::getDigit(const char c){
  return (int)(c - '0');
}

// ���l�𓾂�
int Lexer::getNumber(int& index, const std::string str){
  int num = 0;
  while(index < str.length()){
    if(isdigit(str[index])){ // ���l�ɕϊ�����
      num *= 10;
      num += getDigit(str[index]);
      ++index;
    }else
      break;
  }
  return num;
}

// �����_�ȉ��̐������߂�
double Lexer::getDecimalNumAfterDecimalPoint(int num){
  double decimal = (double) num;
  while(decimal > 1.0){
    decimal /= 10;
  }
  return decimal;
}

// ��؂蕶�����H
bool Lexer::isDelimiter(int& index, const std::string str){
  return (index < str.length() && (str[index] == ' ' || str[index] == ')'))
    || index == str.length();
}

// ���l�g�[�N���𕶎��񂩂���A�ǉ�����
void Lexer::setNumber(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  
  // �����̐ݒ�
  bool isMinus = (str[index] == '-');
  if(isMinus)
    ++index;
  
  // �����񂩂琔�l�𓾂�
  int num = getNumber(index, str);
  
  if(index < str.length() && str[index] == '.'){
    // �����_�����Ă���ꍇ�A�����_�ȉ��̐������߂č��v�̐��l���g�[�N���Ƃ��ēo�^����
    ++index;
    if(index < str.length() && !isdigit(str[index]) ||
       index >= str.length()){
      // ���l�ɐ����łȂ������������Ă���ꍇ�́A�G���[�𓊂���
      throw TokenException(table.size() - 1, index,
			   NUMBER_ANALYSIS_ERROR,
			   str.substr(0, index));
    }
    
    int numAfterDecimal = getNumber(index, str); // �����_�ȉ��̐������߂�
    if(isDelimiter(index, str)){
      // ��؂蕶���ŁA���l�����������ꍇ
      // �����ɒ���
      double decimalNum =
	(double) num + getDecimalNumAfterDecimalPoint(numAfterDecimal);
      // ����������
      decimalNum *= (isMinus ? -1 : 1);
      table[table.size() - 1].push_back(new Double(startRow, startColmn,
						   endRow, index,
						   decimalNum));
    }else{
      // ���l�ɐ����łȂ������������Ă���ꍇ�́A�G���[�𓊂���
      throw TokenException(table.size() - 1, index,
			   NUMBER_ANALYSIS_ERROR,
			   str.substr(0, index + 1));
    }
  }else if(isDelimiter(index, str)){
    // �����l�̏ꍇ
    num *= (isMinus ? -1 : 1);
    table[table.size() - 1].push_back(new Num(startRow, startColmn,
					      endRow, index,
					      num));
  }else{
    // ���l�ɐ����łȂ������������Ă���ꍇ�́A�G���[�𓊂���
    throw TokenException(table.size() - 1, index,
			 NUMBER_ANALYSIS_ERROR,
			 str.substr(0, index + 1));
  }
}

// �����ʂ̃g�[�N����ǉ�
void Lexer::setLeftParam(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
  table[table.size() - 1].push_back(new LeftParam(startRow, startColmn,
						  endRow, endColmn));
  ++index;
}

// �E���ʂ̃g�[�N����ǉ�
void Lexer::setRightParam(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
  table[table.size() - 1].push_back(new RightParam(startRow, startColmn,
						   endRow, endColmn));
  ++index;
}

// �g�����ʎq�p�̕������H
bool Lexer::isExtendedIdentifier(char c){
  return isalnum(c) ||
    (c == '+') || (c == '-') ||
    (c == '.') || (c == '*') ||
    (c == '/') || (c == '<') ||
    (c == '=') || (c == '>') ||
    (c == '!') || (c == '?') ||
    (c == ':') || (c == '$') ||
    (c == '%') || (c == '_') ||
    (c == '&') || (c == '~') ||
    (c == '^');
}

// �������؂�o��
std::string Lexer::getString(int& index, const std::string str){
  std::string sc_string = "";
  while(index < str.length() && str[index] != '\"'){
    sc_string += str[index];
    ++index;
  }
  return sc_string;
}

// ������g�[�N����ǉ�
void Lexer::setString(int& index, const std::string str,
		      const std::string sc_string, // ��������������
		      int startRow, // ������̎n�܂�̍s
		      int startColmn, // ������̎n�܂�̗�
		      int endRow, // �I���̍s
		      int endColmn // �I���̗�
		      ){
  table[table.size() - 1].push_back(new ScString(startRow, startColmn,
						 endRow, endColmn,
						 sc_string));
  ++index;
}

// ���ʎq�̃g�[�N����ǉ�
void Lexer::setWord(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  std::string word = "";
  while(isExtendedIdentifier(str[index])){
    word += str[index];
    ++index;
  }
  if(isDelimiter(index, str)){
    table[table.size() - 1].push_back(new Word(startRow, startColmn,
					       endRow, index, word));
  }else{
    throw TokenException(table.size() - 1, index,
		     IDENTIFIER_ANALYSIS_ERROR,
		     str.substr(0, index + 1));
  }
}

void Lexer::setUnknown(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  std::string word = "";
  while(!isDelimiter(index, str)){
    word += str[index];
    ++index;
  }
  table[table.size() - 1].push_back(new Unknown(startRow, startColmn,
						endRow, index, word));
}

// �o�b�N�N�H�[�g�̃g�[�N����ǉ�
void Lexer::setQuote(int& index, std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
  table[table.size() - 1].push_back(new Quote(startRow, startColmn,
					      endRow, endColmn));
  ++index;
}

void Lexer::setDot(int& index, std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
  table[table.size() - 1].push_back(new Dot(startRow, startColmn,
					    endRow, endColmn));
  ++index;
}

void Lexer::setSpace(std::string& str, int num){
  std::string space(num, ' ');
  str += space;
}

std::string Lexer::getCode(int lineNum){
  std::string ret;
  int prevIndex = 0;
  for(int i = 0; i < table[lineNum].size(); ++i){
    Token* token = table[lineNum][i];
    int spaceNum = token->getStartColmn() - prevIndex;
    setSpace(ret, spaceNum);
    ret += token->getCode();
    prevIndex = token->getEndColmn();
  }
  return ret;
}

std::string Lexer::getCode(){
  return getCode(currentRow);
}

std::string Lexer::getStringUpToFirstDelimiter(std::string& str, char delimiter){
  for(int i = 0; i < str.length(); ++i){
    if(str[i] == delimiter){
      return str.substr(0, i);
    }
  }
  return str;
}

void Lexer::setSharp(int& index, std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
  table[table.size() - 1].push_back(new Sharp(startRow, startColmn,
					      endRow, endColmn));
  ++index;
}

void Lexer::setBackSlash(int& index,std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
    table[table.size() - 1].push_back(new BackSlash(startRow, startColmn,
						    endRow, endColmn));
  ++index;
}
  
void Lexer::show(){
  for(int i = 0; i < table.size(); ++i){
    for(int j = 0; j < table[i].size(); ++j){
      switch(table[i][j]->getType()){
      case LEFT_PARAM:
	std::cout << "Left (" << std::endl;;
	break;
      case RIGHT_PARAM:
	std::cout << "RIGHT )" << std::endl;;
	break;
      case NUM:
	std::cout << "NUM " << ((Num*)(table[i][j]))->getVal() << std::endl;
	break;
      case DOUBLE:
	std::cout << "DOUBLE " << ((Double*)(table[i][j]))->getVal() << std::endl;
	break;
      case STRING:
	std::cout << "STR " << ((ScString*)(table[i][j]))->getString() << std::endl;
	break;
      case WORD:
	std::cout << "WORD " << ((Word*)(table[i][j]))->getName() << std::endl;
	break;
      case QUOTE:
	std::cout << "QUOTE " << "\'" << std::endl;
	break;
      case SHARP:
	std::cout << "SHARP " << "#" << std::endl;
	break;
      case BACK_SLASH:
	std::cout << "BACK SLASH " << "\\" << std::endl;
      }
    }
  }
}

// �S�Ẵg�[�N������͂�����o��
void Lexer::scan(){
  std::cout << file_name << std::endl;
  std::ifstream in(file_name.c_str());
  if(!in)
    throw std::string("File is not found");
  
  table.push_back(std::vector<Token*>());
  int index = 0; // ���͍s�̌��݂̉�͒��̃C���f�b�N�X�A��������1���̃g�[�N�����J��Ԃ����
  std::string line; // 1�s���̓���

  std::string multi_row_string = ""; // �����s�̕������ێ�����o�b�t�@�[
  bool isKeepString = false; // �����񂪕����s�����Ă��邩�H
  int startRow; // �����񂪕����s�����Ă���ꍇ�ɁA���̕����񂪎n�܂��Ă���s�A��
  int startColmn;
  
  while(getline(in, line)){
    // ����1�s���ɂ���g�[�N����ێ�����x�N�g����ǉ�
    table.push_back(std::vector<Token*>());
    if(line.length() == 0)
      continue;

    // 1�s���ɂ��ČJ��Ԃ��g�[�N�������
    while(index < line.length()){
      if(isKeepString){
	// �����񂪕����s�����Ă���ꍇ
	multi_row_string += getString(index, line);
	if(index < line.length() && line[index] == '\"'){
	  // �����񂪏I����Ă���ꍇ
	  setString(index, line, multi_row_string,
		    startRow, startColmn,
		    table.size() - 1, index);
	  multi_row_string = "";
	  isKeepString = false;
	}else{ // �����񂪂܂������ꍇ�́A���̊Ԃ̉��s������
	  multi_row_string += '\n';
	}
      }
      
      if(isKeepString)
	continue;
      
      // ���ʂȋ�s���΂�
      setIndexAfterSkippingSpace(index, line);

      if(index >= line.length())
	break;
      
      if(isdigit(line[index])){
	// ���̐��̏ꍇ
	setNumber(index, line);
      }else if(line[index] == '-' &&
	       index + 1 < line.length() &&
	       isdigit(line[index + 1])){
	// ���̐��̏ꍇ
	setNumber(index, line);
      }else if(line[index] == '('){
	// ������
	setLeftParam(index, line);
      }else if(line[index] == ')'){
	// �E����
	setRightParam(index, line);
      }else if(line[index] == '.'){
	// dot
	setDot(index, line);
      }else if(line[index] == '`' || line[index] == '\''){
	// back quote
	setQuote(index, line);
      }else if(line[index] == '#'){
	setSharp(index, line);
      }else if(line[index] == '\\'){
	setBackSlash(index, line);
      }else if(line[index] == '\"'){
	if(index > 0 && line[index-1] == '\\')
	  setUnknown(index, line);
	// ������̏ꍇ
	startColmn = index; // �n�܂�̗���L�^���Ă���
	++index;
	// ����������
	multi_row_string += getString(index, line);
	if(index < line.length() && line[index] == '\"'){
	  // ������1�s�Ŋ������Ă���ꍇ
	  setString(index, line, multi_row_string,
		    table.size() - 1, startColmn,
		    table.size() - 1, index + 1);
	  multi_row_string = "";
	}else{
	  // �����łȂ��ꍇ�A�n�܂�̍s���L�^���A�c�����邽�߂Ƀt���O��ݒ�
	  startRow = table.size() - 1;
	  multi_row_string += '\n';
	  isKeepString = true;
	} 
      }else if(isExtendedIdentifier(line[index])){
	// ���ʎq
	setWord(index, line);
      }else if(line[index] == ';'){
	// �R�����g�͍s���܂Ŕ�΂�
	break;
      }else{
	setUnknown(index, line);
      }
    }
    index = 0; //���̍s�̐擪���w���悤�ɐݒ�
  }

  if(isKeepString){
    // �����񂪕��Ă��Ȃ��ꍇ

    // �R�[�h�̕���
    std::string code = getCode(startRow);
    int lastColmn = table[startRow][table[startRow].size() - 1]->getEndColmn();
    setSpace(code, startColmn - lastColmn);
    std::string firstStr = getStringUpToFirstDelimiter(multi_row_string, '\n');
    
    throw TokenException(startRow, startColmn,
			 UNCLOSED_STRING_ERROR,
			 code + "\"" + firstStr);
  }

  // �g�[�N���𑖍��ł���悤�ɐݒ�
  currentRow = 0;
  currentColmn = 0;
  next();
};