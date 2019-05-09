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

		// 设置待解析的源代码
		void SetSourceText(string source_text);

		// 对当前指定的源代码进行词法分析
		void Parse();

		// 返回保存单词符号的数组
		vector<Symbol>& GetSymbols();

		// 获取单词符号类型的助记符
		string GetMnemonicsOfSymbolType(SymbolType symbol_type);

	private:
		// 定义单词符号种别的助记符
		void defineMnemonicsForSymbolType(SymbolType symbol_type, string mnemonics);
		
		// 关联单词符号种别与关键词
		void associateSymbolTypeWithKeyword(SymbolType symbol_type, string keyword);

		// 判断word是否为关键词
		bool isKeyword(string word);

		// 判断character是否为合法的标识符字符
		bool isLegalIdentifierCharacter(char character);

		// 返回关键词对应的单词符号种别
		SymbolType getSymbolOfKeyword(string keyword);

		// 将分析得到的单词符号保存到容器中
		void collectSymbol(SymbolType symbol_type, string value);


		string source_text_;                    // 源代码
		unsigned current_index_;                // 源代码中下一个待分析的字符的下标
		unsigned line_number_, column_number_;  // 源代码中的current_idx所指向字符的行号和列号

		vector<Symbol> symbols_;  // 用以保存单词符号的数组

		map<string, SymbolType> mnemonics_to_symbol_type_;  // 保存助记符对应的单词符号种别
		map<string, SymbolType> keyword_to_symbol_type_;    // 保存关键词对应的单词符号种别
		map<SymbolType, string> symbol_type_to_mnemonics_;  // 保存单词符号种别对应的助记符
		map<SymbolType, string> symbol_type_to_keyword_;    // 保存单词符号种别对应的关键词
	};
}
