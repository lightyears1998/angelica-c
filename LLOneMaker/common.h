// commom.h
//
// 定义单词符号的种别enum SymbolType，
// 以及单词符号struct Symbol。


#pragma once

#include <string>
#include <ostream>

namespace angelica
{
	using namespace std;

	// 单词符号的种别
	// TERMINAL    - 终结符
	// NONTERMINAL - 非终结符
	// STRUCTURE   - 文法中的“→”、“|”等结构性字符
	enum class SymbolType : int
	{
		TERMINAL, NONTERMINAL, STRUCTURE
	};

	// 单词符号
	// 空终结符使用Symbol(SymbolType::TERMINAL, "ε")表示。
	struct Symbol
	{
		SymbolType type;  // 单词符号种别
		string value;     // 单词符号的值

		// 默认构造空的终结符。
		Symbol();

		// 使用单一value进行构造时，默认type为STRUCTRUE。
		Symbol(const string& value);
		
		Symbol(SymbolType type, const string& value);

		bool operator == (const Symbol& rhs) const {
			return type == rhs.type && value == rhs.value;
		}

		bool operator != (const Symbol& rhs) const {
			return type != rhs.type || value != rhs.value;
		}

		bool operator < (const Symbol& rhs) const {
			if (type != rhs.type) {
				return type < rhs.type;
			}
			return value < rhs.value;
		}
	};

	ostream& operator << (ostream&out, const Symbol sym);

	const Symbol NULL_SYMBOL = Symbol(SymbolType::TERMINAL, "ε");
}
