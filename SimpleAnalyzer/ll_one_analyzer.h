// ll_one_analyzer.h
//
// LL(1)分析器class LLOneAnalyzer的定义


#pragma once

#include "common.h"

#include <string>
#include <map>
#include <utility>


namespace angelica
{
	// LL(1)分析表
	class LLOneAnalyzer
	{
	public:
		LLOneAnalyzer();

		// 定义语法符号
		void DefineGrammarSymbol(string mark, GrammarSymbolType type);

		// 定义文法的开始符号
		void DefineStartSymbol(string mark);

		// 定义语法规则
		void DefineGrammarRule(pair<string, string> line_column_pair, pair<string, string> left_right_part_pair);

	private:
		// 取得某个语法符号的类型
		GrammarSymbolType getGrammarSymbolType(string mark);
		
		string start_symbol_;                                    // 文法的开始符号
		map<string, GrammarSymbolType> symbols_;                 // 语法符号表
		map<pair<string, string>, pair<string, string>> table_;  // 分析表
	};
}
