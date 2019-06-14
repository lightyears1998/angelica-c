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
		TERMINAL, NONTERMINAL, STRUCTURE
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
