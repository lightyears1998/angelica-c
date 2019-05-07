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

	void Parser::Parse(string source_code)
	{
		symbols_.clear();  // 在词法分析开始前，清空保存单词符号的容器

		for (size_t idx = 0; idx < source_code.length(); ++idx)
		{
			string token;  // 用于保存单词符号的字符串
			token = source_code[idx];  // 将token初始化为input[idx]

			if (isspace(token[0])) {  // 滤除空白字符
				continue;
			}

			if (token[0] == '=') { // 识别为“=”或“==”
				if (idx + 1 < source_code.length() && source_code.substr(idx, 2) == "==")
				{  // “==”
					symbols_.push_back(Symbol(SymbolType::RELOP_EQ, ""));
				}
				else
				{  // “=”
					symbols_.push_back(Symbol(SymbolType::ASSIGNMENT, ""));
				}

				continue;
			}

			if (token[0] == '+') {  // “+”
				symbols_.push_back(Symbol(SymbolType::PLUS, ""));
				continue;
			}

			if (token[0] == '-') {  // “-”
				symbols_.push_back(Symbol(SymbolType::SUBSTRACT, ""));
				continue;
			}

			if (token[0] == '*') {  // “*”
				symbols_.push_back(Symbol(SymbolType::MULTIPLE, ""));
				continue;
			}

			if (token[0] == '/') {  // “//”、“/*”或“/”
				if (idx + 1 < source_code.length())
				{
					if (source_code[idx + 1] == '/')
					{  // “//”
						++idx;
						while (idx < source_code.length() && source_code[idx] != '\n') 
							++idx;  // 滤除注释

						continue;
					}
					else
					{  // “/*”
						++idx;
						while (idx + 1 < source_code.length() && source_code.substr(idx, 2) != "*/")
							++idx;  // 滤除注释
						
						continue;
					}
				}
				else
				{  // “/”
					symbols_.push_back(Symbol(SymbolType::DIVIDE, ""));

					continue;
				}
			}

			if (token[0] == '(') {  // “(”
				symbols_.push_back(Symbol(SymbolType::LS_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == ')') {  // “)”
				symbols_.push_back(Symbol(SymbolType::RS_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == '[') {  // “[”
				symbols_.push_back(Symbol(SymbolType::LM_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == ']') {  // “]”
				symbols_.push_back(Symbol(SymbolType::RM_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == '{') {  // “{”
				symbols_.push_back(Symbol(SymbolType::LL_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == '}') {  // “}”
				symbols_.push_back(Symbol(SymbolType::RL_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == ',') {  // “,”
				symbols_.push_back(Symbol(SymbolType::COMMA, ""));
				continue;
			}

			if (token[0] == ':') {  // “:”
				symbols_.push_back(Symbol(SymbolType::COLON, ""));
				continue;
			}

			if (token[0] == ';') {  // “;”
				symbols_.push_back(Symbol(SymbolType::SEMICOLON, ""));
				continue;
			}

			if (isalpha(token[0]) || token[0] == '_') {  // 识别为关键词或标识符
				size_t cur = idx + 1;  // 待分析的第一个字符的下标
				while (cur < source_code.length() && (isalpha(source_code[cur]) || isdigit(source_code[cur]) || source_code[cur] == '_')) 
				{
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;  // 回退一个字符
				if (isKeyword(token)) {  // 识别为关键词
					SymbolType type = keyword_to_symbol_type_[token];
					symbols_.push_back(Symbol(type, ""));
				}
				else {  // 识别为标识符
					symbols_.push_back(Symbol(SymbolType::ID, token));
				}
				
				continue;
			}

			if (isdigit(token[0])) {  // 整数（不考虑小数）
				size_t cur = idx + 1;
				while (cur < source_code.length() && isdigit(source_code[cur])) {
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;
				symbols_.push_back(Symbol(SymbolType::INT, token));
				continue;
			}

			if (token[0] == '"') {  // 字符串
				token = "";
				size_t cur = idx + 1;
				while (cur < source_code.length() && source_code[cur] != '"') {  // 不考虑转义字符
					token += source_code[cur];
					cur += 1;
				}

				idx = cur;
				symbols_.push_back(Symbol(SymbolType::STRING, token));
				continue;
			}

			if (token[0] == '>')  // “>”、“>=”
			{
				if (idx + 1 < source_code.length() && source_code[idx + 1] == '=')
				{
					symbols_.push_back(Symbol(SymbolType::RELOP_GE, ""));
					++idx;
					continue;
				}

				symbols_.push_back(Symbol(SymbolType::RELOP_GT, ""));
				continue;
			}

			if (token[0] == '<')  // “<”、“<=”
			{
				if (idx + 1 < source_code.length() && source_code[idx + 1] == '=')
				{
					symbols_.push_back(Symbol(SymbolType::RELOP_LE, ""));
					++idx;
					continue;
				}

				symbols_.push_back(Symbol(SymbolType::RELOP_LT, ""));
				continue;
			}

			if (token[0] == '=')  // “=”、“==”
			{
				if (idx + 1 < source_code.length() && source_code[idx + 1] == '=')
				{
					symbols_.push_back(Symbol(SymbolType::RELOP_EQ, ""));
					++idx;
					continue;
				}
				
				symbols_.push_back(Symbol(SymbolType::ASSIGNMENT, ""));
				continue;
			}

			if (token[0] == '!' && idx + 1 < source_code.length() && source_code[idx+1] == '=')  // “!=”
			{  // 识别为“!=”
				symbols_.push_back(Symbol(SymbolType::RELOP_NEQ, ""));
				++idx;
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

	SymbolType Parser::getSymbolOfKeyword(string keyword)
	{
		return keyword_to_symbol_type_.at(keyword);
	}

	vector<Symbol>& Parser::GetSymbols()
	{
		return symbols_;
	}

	string Parser::GetSymbolString(Symbol symbol)
	{
		string mnemonics = symbol_type_to_mnemonics_[symbol.type];
		string value = symbol.value != "" ? symbol.value : "null";
		return string("(") + mnemonics + string(", ") + value + string(")");
	}
}
