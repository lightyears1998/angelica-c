#include "parser.h"


namespace angelica
{
	using namespace std;

	Parser::Parser()
	{
		// 添加关键词
		keyword_to_symbol_type_["main"] = SymbolType::KEYWORD_MAIN;
		keyword_to_symbol_type_["int"] = SymbolType::KEYWORD_INT;
		keyword_to_symbol_type_["char"] = SymbolType::KEYWORD_CHAR;
		keyword_to_symbol_type_["if"] = SymbolType::KEYWORD_IF;
		keyword_to_symbol_type_["else"] = SymbolType::KEYWORD_ELSE;
		keyword_to_symbol_type_["for"] = SymbolType::KEYWORD_FOR;
		keyword_to_symbol_type_["while"] = SymbolType::KEYWORD_WHILE;
		keyword_to_symbol_type_["return"] = SymbolType::KEYWORD_RETURN;
		keyword_to_symbol_type_["void"] = SymbolType::KEYWORD_VOID;

		// 为单词种别添加助记符
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_MAIN] = "main";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_INT] = "int";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_CHAR] = "char";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_IF] = "if";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_ELSE] = "else";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_FOR] = "for";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_WHILE] = "while";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_RETURN] = "return";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_VOID] = "void";

		symbol_type_to_mnemonics_[SymbolType::STRING] = "STRING";
		symbol_type_to_mnemonics_[SymbolType::ID] = "ID";
		symbol_type_to_mnemonics_[SymbolType::INT] = "INT";
		symbol_type_to_mnemonics_[SymbolType::EQUALS] = "=";
		symbol_type_to_mnemonics_[SymbolType::PLUS] = "+";
		symbol_type_to_mnemonics_[SymbolType::SUBSTRACT] = "-";
		symbol_type_to_mnemonics_[SymbolType::MULTIPLE] = "*";
		symbol_type_to_mnemonics_[SymbolType::DIVIDE] = "/";
		
		symbol_type_to_mnemonics_[SymbolType::LS_PARENTHESIS] = "(";
		symbol_type_to_mnemonics_[SymbolType::RS_PARENTHESIS] = ")";
		symbol_type_to_mnemonics_[SymbolType::LS_PARENTHESIS] = "[";
		symbol_type_to_mnemonics_[SymbolType::RS_PARENTHESIS] = "]";
		symbol_type_to_mnemonics_[SymbolType::LS_PARENTHESIS] = "{";
		symbol_type_to_mnemonics_[SymbolType::RS_PARENTHESIS] = "}";

		symbol_type_to_mnemonics_[SymbolType::COMMA] = ",";
		symbol_type_to_mnemonics_[SymbolType::COLON] = ":";
		symbol_type_to_mnemonics_[SymbolType::SEMICOLON] = ";";

		symbol_type_to_mnemonics_[SymbolType::RELOP_GT] = ">";
		symbol_type_to_mnemonics_[SymbolType::RELOP_LT] = "<";
		symbol_type_to_mnemonics_[SymbolType::RELOP_GE] = ">=";
		symbol_type_to_mnemonics_[SymbolType::RELOP_LE] = "<=";
		symbol_type_to_mnemonics_[SymbolType::RELOP_EQ] = "==";
		symbol_type_to_mnemonics_[SymbolType::RELOP_NEQ] = "!=";
	}

	void Parser::Parse(string source_code)
	{
		for (size_t idx = 0; idx < source_code.length(); ++idx)
		{
			string token(1, source_code[idx]);  // 将token初始化为input[idx]

			if (isspace(token[0])) {  // 滤除空白字符
				continue;
			}

			if (isalpha(token[0])) {  // 关键词或标识符
				size_t cur = idx + 1;  // 待分析的第一个字符的下标
				while (cur < source_code.length() && (isalpha(source_code[cur]) || isdigit(source_code[cur]))) {
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;
				if (isKeyword(token)) {  // 关键词
					SymbolType type = keyword_to_symbol_type_[token];
					symbols_.push_back(Symbol(type, ""));
				}
				else {  // 标识符
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
		}
	}

	void Parser::defineMnemonicsForSymbolType(SymbolType type, string mnemonics)
	{
		symbol_type_to_mnemonics_[type] = mnemonics;
	}

	void Parser::associateSymbolTypeWithKeyword(SymbolType type, string keyword)
	{
		keyword_to_symbol_type_[keyword] = type;
	}

	bool Parser::isKeyword(string word)
	{
		// 若为关键字，则可以在关键字表中找到关键字对应的单词种别。
		return keyword_to_symbol_type_.find(word) != keyword_to_symbol_type_.end();
	}

	SymbolType Parser::getKeywordSymbol(string keyword)
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
