// parser.h
//
// 从输入流中获得终结符、非终结符和文法结构符号的Parser。

#pragma once

#include "common.h"

#include <vector>
#include <iostream>

namespace angelica
{
	using namespace std;

	class Parser
	{
	private:
		istream &in_;

	public:
		Parser(istream& in) : in_(in) {};
		~Parser() = default;

		// 从输入流中解析单词符号，直到遇到换行符。
		vector<Symbol> ParseLineFromInputStream();
	};
}
