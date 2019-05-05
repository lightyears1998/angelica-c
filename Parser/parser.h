#pragma once

#include "common.h"

#include <string>
#include <vector>
#include <map>


namespace angelica
{
	using namespace std;

	// ´Ê·¨·ÖÎöÆ÷
	class Parser
	{
	public:
		Parser();
		
		void Parse(string source_code);

		bool IsKeyword(string word);

		vector<Symbol>& GetSymbols();
		string GetSymbolString(Symbol symbol);

	private:
		void addKeyword(string keyword, SymbolType type);

		vector<Symbol> symbols_;
		map<string, SymbolType> keyword_to_symbol_type_;
		map<SymbolType, string> symbol_type_to_keyword_;
		map<SymbolType, string> symbol_type_to_mnemonics_;
	};
}
