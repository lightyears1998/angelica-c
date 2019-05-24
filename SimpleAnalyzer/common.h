#pragma once

#include <string>

namespace angelica
{
	using namespace std;
	
	// 定义Symbol类型为string类型的同义词
	using Symbol = string;

	// 语法符号类型枚举
	enum class GrammarSymbolType
	{
		TerminalSymbol, NonTerminalSymbol  // 终结符和非终结符
	};
}
