#include "parser.h"


namespace angelica
{
	using namespace std;

	Parser::Parser()
	{
		// 添加关键词
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_MAIN, "main");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_INT, "int");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_CHAR, "char");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_IF, "if");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_ELSE, "else");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_FOR, "for");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_WHILE, "while");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_RETURN, "return");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_VOID, "void");

		// 为单词种别添加助记符
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_MAIN, "main");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_INT, "int");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_CHAR, "char");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_IF, "if");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_ELSE, "else");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_FOR, "for");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_WHILE, "while");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_RETURN, "return");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_VOID, "void");
		
		defineMnemonicsForSymbolType(SymbolType::STRING, "STRING");
		defineMnemonicsForSymbolType(SymbolType::ID, "ID");
		defineMnemonicsForSymbolType(SymbolType::INT, "INT");
		defineMnemonicsForSymbolType(SymbolType::ASSIGNMENT, "=");
		defineMnemonicsForSymbolType(SymbolType::PLUS, "+");
		defineMnemonicsForSymbolType(SymbolType::SUBSTRACT, "-");
		defineMnemonicsForSymbolType(SymbolType::MULTIPLE, "*");
		defineMnemonicsForSymbolType(SymbolType::DIVIDE, "/");

		defineMnemonicsForSymbolType(SymbolType::LS_PARENTHESIS, "(");
		defineMnemonicsForSymbolType(SymbolType::RS_PARENTHESIS, ")");
		defineMnemonicsForSymbolType(SymbolType::LM_PARENTHESIS, "[");
		defineMnemonicsForSymbolType(SymbolType::RM_PARENTHESIS, "]");
		defineMnemonicsForSymbolType(SymbolType::LL_PARENTHESIS, "{");
		defineMnemonicsForSymbolType(SymbolType::RL_PARENTHESIS, "}");

		defineMnemonicsForSymbolType(SymbolType::COMMA, ",");
		defineMnemonicsForSymbolType(SymbolType::COLON, ":");
		defineMnemonicsForSymbolType(SymbolType::SEMICOLON, ";");

		defineMnemonicsForSymbolType(SymbolType::RELOP_GT, ">");
		defineMnemonicsForSymbolType(SymbolType::RELOP_LT, "<");
		defineMnemonicsForSymbolType(SymbolType::RELOP_GE, ">=");
		defineMnemonicsForSymbolType(SymbolType::RELOP_LE, "<=");
		defineMnemonicsForSymbolType(SymbolType::RELOP_EQ, "==");
		defineMnemonicsForSymbolType(SymbolType::RELOP_NEQ, "!=");
	}

	void Parser::Parse()
	{
		while (current_index_ < source_text_.length())
		{
			string token;  // 用于保存单词符号的字符串
			token = source_text_[current_index_];  // 将token初始化为待分析的第一个字符

			if (isspace(token[0])) {  // 滤除空白字符
				if (token[0] == '\n') {
					++current_index_;
					++line_number_, column_number_ = 1;
				}
				else {
					++current_index_;
					++column_number_;
				}
				continue;
			}

			if (token[0] == '=') { // 识别为“=”或“==”
				if (current_index_ + 1 < source_text_.length() && source_text_.substr(current_index_, 2) == "==")
				{  // “==”
					collectSymbol(SymbolType::RELOP_EQ, "");
					current_index_ += 2;
					column_number_ += 2;
				}
				else
				{  // “=”
					collectSymbol(SymbolType::ASSIGNMENT, "");
					current_index_ += 1;
					column_number_ += 1;
				}
				continue;
			}

			if (token[0] == '+') {  // “+”
				collectSymbol(SymbolType::PLUS, "");
				++current_index_;
				++column_number_;
				continue;
			}

			if (token[0] == '-') {  // “-”
				collectSymbol(SymbolType::SUBSTRACT, "");
				++current_index_;
				++column_number_;
				continue;
			}

			if (token[0] == '*') {  // “*”
				collectSymbol(SymbolType::MULTIPLE, "");
				++current_index_;
				++column_number_;
				continue;
			}

			if (token[0] == '/') {  // “//”、“/*”或“/”
				if (current_index_ + 1 < source_text_.length())
				{
					if (source_text_[current_index_ + 1] == '/')
					{  // “//”
						current_index_ += 2;
						while (current_index_ < source_text_.length() && source_text_[current_index_] != '\n')
							++current_index_;  // 滤除注释
						++current_index_;
						++line_number_, column_number_ = 1;
						continue;
					}
					else if (source_text_[current_index_ + 1] == '*')
					{  // “/*”
						current_index_ += 2, column_number_ += 2;
						while (current_index_ + 1 < source_text_.length() && source_text_.substr(current_index_, 2) != "*/")
						{
							++current_index_;
							if (source_text_[current_index_] != '\n') {
								++column_number_;
							}
							else {
								++line_number_, column_number_ = 1;
							}
						}
						current_index_ += 2, column_number_ += 2;
						continue;
					}
				}
				else
				{  // “/”
					collectSymbol(SymbolType::DIVIDE, "");
					++current_index_, ++column_number_;
					continue;
				}
			}

			if (token[0] == '(') {  // “(”
				collectSymbol(SymbolType::LS_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ')') {  // “)”
				collectSymbol(SymbolType::RS_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == '[') {  // “[”
				collectSymbol(SymbolType::LM_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ']') {  // “]”
				collectSymbol(SymbolType::RM_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == '{') {  // “{”
				collectSymbol(SymbolType::LL_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == '}') {  // “}”
				collectSymbol(SymbolType::RL_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ',') {  // “,”
				collectSymbol(SymbolType::COMMA, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ':') {  // “:”
				collectSymbol(SymbolType::COLON, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ';') {  // “;”
				collectSymbol(SymbolType::SEMICOLON, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (isalpha(token[0]) || token[0] == '_') {  // 关键词或标识符以字母或下划线开头
				unsigned end_of_identifier_index = current_index_ + 1;  // 关键字或标志符最后一个字符在源代码中的下标
				while (end_of_identifier_index < source_text_.length() && isLegalIdentifierCharacter(source_text_[end_of_identifier_index]))
				{
					token += source_text_[end_of_identifier_index];
					++end_of_identifier_index;
				}
				--end_of_identifier_index;  // 回退一个字符
				if (isKeyword(token)) {  // 识别为关键词
					collectSymbol(getSymbolOfKeyword(token) , "");
				}
				else {  // 识别为标识符
					collectSymbol(SymbolType::ID, token);
				}
				column_number_ += end_of_identifier_index - current_index_ + 1;
				current_index_ = end_of_identifier_index + 1;
				continue;
			}

			if (isdigit(token[0])) {  // 整数（不考虑小数）
				unsigned end_of_number_index = current_index_ + 1;
				while (end_of_number_index < source_text_.length() && isdigit(source_text_[end_of_number_index])) {
					token += source_text_[end_of_number_index];
					++end_of_number_index;
				}
				--end_of_number_index;  // 回退一个字符
				collectSymbol(SymbolType::INT, token);
				column_number_ += end_of_number_index - current_index_ + 1;
				current_index_ = end_of_number_index + 1;
				continue;
			}

			if (token[0] == '"') {  // 字符串
				token = "";
				unsigned end_of_string_index = current_index_ + 1;
				while (end_of_string_index < source_text_.length() && source_text_[end_of_string_index] != '"') {  // 不考虑转义字符
					token += source_text_[end_of_string_index];
					end_of_string_index += 1;
				}
				collectSymbol(SymbolType::STRING, token);
				column_number_ += end_of_string_index - current_index_ + 1;
				current_index_ = end_of_string_index + 1;
				continue;
			}

			if (token[0] == '>')  // “>”、“>=”
			{
				if (current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // “>=”
				{
					collectSymbol(SymbolType::RELOP_GE, "");
					current_index_ += 2, column_number_ += 2;
					continue;
				}
				else {
					collectSymbol(SymbolType::RELOP_GT, "");
					++current_index_, ++column_number_;
					continue;
				}
			}

			if (token[0] == '<')  // “<”、“<=”
			{
				if (current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // “<=”
				{
					collectSymbol(SymbolType::RELOP_LE, "");
					current_index_ += 2, column_number_ += 2;
					continue;
				}
				else {  // “<”
					collectSymbol(SymbolType::RELOP_LT, "");
					++current_index_, ++column_number_;
					continue;
				}
			}

			if (token[0] == '=')  // “=”、“==”
			{
				if (current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // “==”
				{
					collectSymbol(SymbolType::RELOP_EQ, "");
					current_index_ += 2, column_number_ += 2;
					continue;
				}
				else {  // “=”
					collectSymbol(SymbolType::ASSIGNMENT, "");
					++current_index_, ++column_number_;
				}
				
				continue;
			}

			if (token[0] == '!' && current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // “!=”
			{  // 识别为“!=”
				collectSymbol(SymbolType::RELOP_NEQ, "");
				++current_index_ += 2, column_number_ += 2;
				continue;
			}

			// 如果没有被任何一个if语句捕捉，则应该报告错误
			throw new exception("输入内容不合词法。");
		}
	}

	void Parser::defineMnemonicsForSymbolType(SymbolType symbol_type, string mnemonics)
	{
		symbol_type_to_mnemonics_[symbol_type] = mnemonics;
		mnemonics_to_symbol_type_[mnemonics] = symbol_type;
	}

	void Parser::associateSymbolTypeWithKeyword(SymbolType symbol_type, string keyword)
	{
		symbol_type_to_keyword_[symbol_type] = keyword;
		keyword_to_symbol_type_[keyword] = symbol_type;
	}

	bool Parser::isKeyword(string word)
	{
		// 若为关键字，则可以在关键字表中找到关键字对应的单词种别。
		return keyword_to_symbol_type_.find(word) != keyword_to_symbol_type_.end();
	}

	bool Parser::isLegalIdentifierCharacter(char character)
	{
		return isalpha(character) || isdigit(character) || character == '_';
	}

	SymbolType Parser::getSymbolOfKeyword(string keyword)
	{
		return keyword_to_symbol_type_.at(keyword);
	}

	void Parser::collectSymbol(SymbolType symbol_type, string value)
	{
		symbols_.push_back(Symbol(symbol_type, value, line_number_, column_number_));
	}

	vector<Symbol>& Parser::GetSymbols()
	{
		return symbols_;
	}

	void Parser::SetSourceText(string source_text)
	{
		source_text_ = source_text;
		current_index_ = 0;
		line_number_ = 1, column_number_ = 1;
		symbols_.clear();
	}

	string Parser::GetMnemonicsOfSymbolType(SymbolType symbol_type)
	{
		return symbol_type_to_mnemonics_[symbol_type];
	}
}
