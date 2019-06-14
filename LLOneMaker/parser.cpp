// parser.cpp
//
// 词法分析器class Parser的实现。 


#include "parser.h"


namespace angelica
{
	using namespace std;

	Parser::Parser()
	{
		// 由子类需要重写此函数以添加特定的单词符号规则
		// 参考class CParser
	}

	void Parser::Parse()
	{
		// 子类需要重写此函数以添加特定的单词符号规则
		// 参考class CParser
	}

	void Parser::defineMnemonicsForSymbolType(SymbolType symbol_type, string mnemonics)
	{
		symbol_type_to_mnemonics_[symbol_type] = mnemonics;
		mnemonics_to_symbol_type_[mnemonics] = symbol_type;
	}

	void Parser::associateSymbolTypeWithKeyword(SymbolType symbol_type, string keyword)
	{
		symbol_type_to_keyword_[symbol_type] = keyword;
		keyword_to_symbol_type_[keyword] = symbol_type;
	}

	bool Parser::isKeyword(string word)
	{
		// 若为关键字，则可以在关键字表中找到关键字对应的单词种别。
		return keyword_to_symbol_type_.find(word) != keyword_to_symbol_type_.end();
	}

	bool Parser::isLegalIdentifierCharacter(char character)
	{
		return isalpha(character) || isdigit(character) || character == '_';
	}

	SymbolType Parser::getSymbolOfKeyword(string keyword)
	{
		return keyword_to_symbol_type_.at(keyword);
	}

	void Parser::collectSymbol(SymbolType symbol_type, string value)
	{
		symbols_.push_back(Symbol(symbol_type, value, line_number_, column_number_));
	}

	vector<Symbol>& Parser::GetSymbols()
	{
		return symbols_;
	}

	void Parser::SetSourceText(string source_text)
	{
		source_text_ = source_text;
		current_index_ = 0;
		line_number_ = 1, column_number_ = 1;
		symbols_.clear();
	}

	string Parser::GetMnemonicsOfSymbolType(SymbolType symbol_type)
	{
		return symbol_type_to_mnemonics_[symbol_type];
	}
}
