// ll_one_analyzer.h
//
// LL(1)分析器class LLOneAnalyzer的定义


#pragma once

#include "common.h"

#include <string>
#include <map>
#include <vector>
#include <utility>


namespace angelica
{
	using namespace std;	

	// LL(1)分析器
	class LLOneAnalyzer
	{
	public:
		LLOneAnalyzer();

		// 定义文法的开始符号
		void DefineStartSymbol(Symbol symbol);

		// 定义语法规则
		void DefineGrammarRule(pair<Symbol, Symbol> line_column_pair, vector<Symbol> right_part);

		// 输出语法规则
		void PrintGrammarRules();

		// 以表格形式输出语法规则
		void PrintGrammarRulesTable();

		// 判断一个句子是否符合所给定的文法
		bool Judge(vector<Symbol> sequence);

	private:
		
		Symbol start_symbol_;  // 文法的开始符号
		map<pair<Symbol, Symbol>, vector<Symbol>> table_;  // 分析表
	};
}
