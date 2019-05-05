#pragma once

#include "common.h"

#include <string>
#include <vector>
#include <map>


namespace angelica
{
	using namespace std;

	// 词法分析器
	class Parser
	{
	public:
		Parser();
		
		// 对指定souce_code进行词法分析
		void Parse(string source_code);

		// 返回保存单词符号的数组
		vector<Symbol>& GetSymbols();

		// 返回单词符号的字符串表示
		string GetSymbolString(Symbol symbol);

	private:
		// 定义单词符号种别的助记符
		void defineMnemonicsForSymbolType(SymbolType type, string mnemonics);
		
		// 关联单词符号种别与关键词
		void associateSymbolTypeWithKeyword(SymbolType type, string keyword);

		// 判断word是否为关键词
		bool isKeyword(string word);

		// 返回关键词对应的单词符号种别
		SymbolType getKeywordSymbol(string keyword);

		vector<Symbol> symbols_;  // 用以保存单词符号的数组
		map<string, SymbolType> keyword_to_symbol_type_;  // 保存关键词对应的单词符号种别
		map<SymbolType, string> symbol_type_to_mnemonics_;  // 保存单词符号种别对应的助记符
	};
}
