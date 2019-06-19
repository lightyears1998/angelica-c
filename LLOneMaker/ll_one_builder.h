// ll_one_builder.h
//
// LL(1)分析表生成器的定义。

#pragma once

#include "common.h"
#include "parser.h"
#include "ll_one_analyzer.h"

namespace angelica {
	// LL(1)分析表生成器
	// 能自动生成符合LL(1)规则的分析器。
	class LLOneBuilder
	{
	private:
		Parser parser_;

	public:
		LLOneBuilder(Parser &parser) : parser_(parser) {};

		// 从Parser中获取表示LL(1)文法的符号，并返回对应文法的LL(1)分析器。
		LLOneAnalyzer BuildAnalyzer();
	};
}
