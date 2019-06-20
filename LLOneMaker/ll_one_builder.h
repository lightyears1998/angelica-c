// ll_one_builder.h
//
// LL(1)分析表生成器的定义。

#pragma once

#include "common.h"
#include "parser.h"
#include "ll_one_analyzer.h"

#include <set>
#include <map>
#include <functional>

namespace angelica {
	// LL(1)分析表生成器
	// 能自动生成符合LL(1)规则的分析器。
	class LLOneBuilder
	{
	private:
		Parser parser_;                             // 输入文法使用的词法分析器

		LLOneAnalyzer analyzer;                     // 与输入文法对应的分析器
		set<Symbol> nonterminal_set;                // 保存所有非终结符的集合
		Symbol start_symbol;                        // 保存文法的开始符号
		map<Symbol, vector<Symbol>> left_to_right;  // 左部非终结符到右部符号的映射

	public:
		LLOneBuilder(Parser &parser) : parser_(parser) {};

		// 从Parser中获取表示LL(1)文法的符号，并返回对应文法的LL(1)分析器。
		LLOneAnalyzer BuildAnalyzer();

	private:
		// 从Parser中获取文法输入
		void getInputFromParser();
		
		// 消除左递归
		void diminishLeftRecursion();

		// 消除回溯
		void removeLookBack();

		// 获取一个终结符所可能推导出的第一个非终结符的集合（First集）
		set<Symbol> getPossibleFirstTerminalSymbol(Symbol left);

		// 获取一个终结符之后所可能推导出的第一个非终结符的集合（Follow集）
		set<Symbol> getPossibleFollowTerminalSymbol(Symbol left);

		// 打印非终结符集合
		void printNonterminalSymbolSet();
	
		// 打印First集
		void printFirstSet();

		// 打印Follow集
		void printFollowSet();

		// 生成文法对应的分析器
		void buildAnalyzer();
	};
}
