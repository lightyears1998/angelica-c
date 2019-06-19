// commom.h
//
// 定义单词符号的种别enum SymbolType，
// 以及单词符号struct Symbol。


#pragma once

#include <string>


namespace angelica
{
	using namespace std;

	// 单词符号的种别
	enum class SymbolType : int
	{
		KEYWORD_MAIN = 1,
		KEYWORD_INT, KEYWORD_CHAR, KEYWORD_IF, KEYWORD_ELSE,
		KEYWORD_FOR, KEYWORD_WHILE, KEYWORD_RETURN,
		KEYWORD_VOID,
		STRING = 50, ID = 10, INT = 20,
		ASSIGNMENT = 21,  // 赋值符号“=”
		PLUS, SUBSTRACT, MULTIPLE, DIVIDE,
		LS_PARENTHESIS, RS_PARENTHESIS, // 左小括号，右小括号
		LM_PARENTHESIS, RM_PARENTHESIS,
		LL_PARENTHESIS, RL_PARENTHESIS,
		COMMA, COLON, SEMICOLON,  // 逗号，冒号，分号
		RELOP_GT, RELOP_LT, RELOP_GE, RELOP_LE, RELOP_EQ, RELOP_NEQ
	};

	// 单词符号
	struct Symbol
	{
		SymbolType type;  // 单词符号种别
		string value;     // 单词符号的值
		unsigned line_number, column_number;  // 所在的行号和列号


		Symbol(SymbolType symbol_type, string value, unsigned line_number, unsigned column_number) :
			type(symbol_type), value(value), line_number(line_number), column_number(column_number)
		{};
	};
}