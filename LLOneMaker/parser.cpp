// parser.cpp
//
// �ʷ�������class Parser��ʵ�֡� 


#include "parser.h"


namespace angelica
{
	using namespace std;

	Parser::Parser()
	{
		// ��������Ҫ��д�˺���������ض��ĵ��ʷ��Ź���
		// �ο�class CParser
	}

	void Parser::Parse()
	{
		// ������Ҫ��д�˺���������ض��ĵ��ʷ��Ź���
		// �ο�class CParser
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
		// ��Ϊ�ؼ��֣�������ڹؼ��ֱ����ҵ��ؼ��ֶ�Ӧ�ĵ����ֱ�
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
