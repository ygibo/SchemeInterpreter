#include"Lexer.hpp"
#include"ErrorMessage.hpp"
#include"TokenException.hpp"

Lexer::~Lexer(){
  // 作成した Token を破棄する
  for(int row = 0; row < table.size(); row++){
    for(int colmn = 0; colmn < table[row].size(); ++colmn){
      if(table[row][colmn] != NULL)
	delete table[row][colmn];
    }
  }
}

// トークンのタイプを得る
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

// 空行を飛ばす
void Lexer::skipEmptyRow(){
  skipEmptyRow(currentRow, currentColmn);
}

void Lexer::next(int& row, int& colmn){
  if(table[row].size() == 0){
    // 空行なら飛ばす
    skipEmptyRow(row, colmn);
  }else{
    ++colmn;
    if(colmn >= table[row].size()){
      // その行の終わりになったら,次の空行でない行へ行く
      ++row;
      skipEmptyRow(row, colmn);
    }
  }
}
  
// 次のトークンへ行く
void Lexer::next(){
  next(currentRow, currentColmn);
}

// すべてのトークンを走査したか？
int Lexer::isEnd(){
    return currentRow >= table.size();
}

// 現在走査中の行番号を得る
int Lexer::getLineNum(){
  return currentRow;
}

// 現在走査中のトークンを返す
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

// スペースを飛ばす
void Lexer::setIndexAfterSkippingSpace(int& index,const std::string str){
  while(str[index] == ' ' || str[index] == '\t')
    ++index;
}

int Lexer::getDigit(const char c){
  return (int)(c - '0');
}

// 数値を得る
int Lexer::getNumber(int& index, const std::string str){
  int num = 0;
  while(index < str.length()){
    if(isdigit(str[index])){ // 数値に変換する
      num *= 10;
      num += getDigit(str[index]);
      ++index;
    }else
      break;
  }
  return num;
}

// 小数点以下の数を求める
double Lexer::getDecimalNumAfterDecimalPoint(int num){
  double decimal = (double) num;
  while(decimal > 1.0){
    decimal /= 10;
  }
  return decimal;
}

// 区切り文字か？
bool Lexer::isDelimiter(int& index, const std::string str){
  return (index < str.length() && (str[index] == ' ' || str[index] == ')'))
    || index == str.length();
}

// 数値トークンを文字列から作り、追加する
void Lexer::setNumber(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  
  // 符号の設定
  bool isMinus = (str[index] == '-');
  if(isMinus)
    ++index;
  
  // 文字列から数値を得る
  int num = getNumber(index, str);
  
  if(index < str.length() && str[index] == '.'){
    // 小数点がついている場合、小数点以下の数を求めて合計の数値をトークンとして登録する
    ++index;
    if(index < str.length() && !isdigit(str[index]) ||
       index >= str.length()){
      // 数値に数字でない数がくっついている場合は、エラーを投げる
      throw TokenException(table.size() - 1, index,
			   NUMBER_ANALYSIS_ERROR,
			   str.substr(0, index));
    }
    
    int numAfterDecimal = getNumber(index, str); // 小数点以下の数を求める
    if(isDelimiter(index, str)){
      // 区切り文字で、数値が完成した場合
      // 小数に直す
      double decimalNum =
	(double) num + getDecimalNumAfterDecimalPoint(numAfterDecimal);
      // 符号をつける
      decimalNum *= (isMinus ? -1 : 1);
      table[table.size() - 1].push_back(new Double(startRow, startColmn,
						   endRow, index,
						   decimalNum));
    }else{
      // 数値に数字でない数がくっついている場合は、エラーを投げる
      throw TokenException(table.size() - 1, index,
			   NUMBER_ANALYSIS_ERROR,
			   str.substr(0, index + 1));
    }
  }else if(isDelimiter(index, str)){
    // 整数値の場合
    num *= (isMinus ? -1 : 1);
    table[table.size() - 1].push_back(new Num(startRow, startColmn,
					      endRow, index,
					      num));
  }else{
    // 数値に数字でない数がくっついている場合は、エラーを投げる
    throw TokenException(table.size() - 1, index,
			 NUMBER_ANALYSIS_ERROR,
			 str.substr(0, index + 1));
  }
}

// 左括弧のトークンを追加
void Lexer::setLeftParam(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
  table[table.size() - 1].push_back(new LeftParam(startRow, startColmn,
						  endRow, endColmn));
  ++index;
}

// 右括弧のトークンを追加
void Lexer::setRightParam(int& index, const std::string str){
  int startRow = table.size() - 1;
  int startColmn = index;
  int endRow = startRow;
  int endColmn = index + 1;
  table[table.size() - 1].push_back(new RightParam(startRow, startColmn,
						   endRow, endColmn));
  ++index;
}

// 拡張識別子用の文字か？
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

// 文字列を切り出す
std::string Lexer::getString(int& index, const std::string str){
  std::string sc_string = "";
  while(index < str.length() && str[index] != '\"'){
    sc_string += str[index];
    ++index;
  }
  return sc_string;
}

// 文字列トークンを追加
void Lexer::setString(int& index, const std::string str,
		      const std::string sc_string, // 完成した文字列
		      int startRow, // 文字列の始まるの行
		      int startColmn, // 文字列の始まりの列
		      int endRow, // 終わりの行
		      int endColmn // 終わりの列
		      ){
  table[table.size() - 1].push_back(new ScString(startRow, startColmn,
						 endRow, endColmn,
						 sc_string));
  ++index;
}

// 識別子のトークンを追加
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

// バッククォートのトークンを追加
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

// 全てのトークンを入力から作り出す
void Lexer::scan(){
  std::cout << file_name << std::endl;
  std::ifstream in(file_name.c_str());
  if(!in)
    throw std::string("File is not found");
  
  table.push_back(std::vector<Token*>());
  int index = 0; // 入力行の現在の解析中のインデックス、ここから1つ分のトークンを繰り返し作る
  std::string line; // 1行分の入力

  std::string multi_row_string = ""; // 複数行の文字列を保持するバッファー
  bool isKeepString = false; // 文字列が複数行続いているか？
  int startRow; // 文字列が複数行続いている場合に、その文字列が始まっている行、列
  int startColmn;
  
  while(getline(in, line)){
    // 入力1行分にあるトークンを保持するベクトルを追加
    table.push_back(std::vector<Token*>());
    if(line.length() == 0)
      continue;

    // 1行分について繰り返しトークンを作る
    while(index < line.length()){
      if(isKeepString){
	// 文字列が複数行続いている場合
	multi_row_string += getString(index, line);
	if(index < line.length() && line[index] == '\"'){
	  // 文字列が終わっている場合
	  setString(index, line, multi_row_string,
		    startRow, startColmn,
		    table.size() - 1, index);
	  multi_row_string = "";
	  isKeepString = false;
	}else{ // 文字列がまだ続く場合は、その間の改行を入れる
	  multi_row_string += '\n';
	}
      }
      
      if(isKeepString)
	continue;
      
      // 無駄な空行を飛ばす
      setIndexAfterSkippingSpace(index, line);

      if(index >= line.length())
	break;
      
      if(isdigit(line[index])){
	// 正の数の場合
	setNumber(index, line);
      }else if(line[index] == '-' &&
	       index + 1 < line.length() &&
	       isdigit(line[index + 1])){
	// 負の数の場合
	setNumber(index, line);
      }else if(line[index] == '('){
	// 左括弧
	setLeftParam(index, line);
      }else if(line[index] == ')'){
	// 右括弧
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
	// 文字列の場合
	startColmn = index; // 始まりの列を記録しておく
	++index;
	// 文字列を作る
	multi_row_string += getString(index, line);
	if(index < line.length() && line[index] == '\"'){
	  // 文字列が1行で完結している場合
	  setString(index, line, multi_row_string,
		    table.size() - 1, startColmn,
		    table.size() - 1, index + 1);
	  multi_row_string = "";
	}else{
	  // そうでない場合、始まりの行を記録し、残りを作るためにフラグを設定
	  startRow = table.size() - 1;
	  multi_row_string += '\n';
	  isKeepString = true;
	} 
      }else if(isExtendedIdentifier(line[index])){
	// 識別子
	setWord(index, line);
      }else if(line[index] == ';'){
	// コメントは行末まで飛ばす
	break;
      }else{
	setUnknown(index, line);
      }
    }
    index = 0; //次の行の先頭を指すように設定
  }

  if(isKeepString){
    // 文字列が閉じていない場合

    // コードの復元
    std::string code = getCode(startRow);
    int lastColmn = table[startRow][table[startRow].size() - 1]->getEndColmn();
    setSpace(code, startColmn - lastColmn);
    std::string firstStr = getStringUpToFirstDelimiter(multi_row_string, '\n');
    
    throw TokenException(startRow, startColmn,
			 UNCLOSED_STRING_ERROR,
			 code + "\"" + firstStr);
  }

  // トークンを走査できるように設定
  currentRow = 0;
  currentColmn = 0;
  next();
};
