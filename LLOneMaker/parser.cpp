#include "parser.h"

namespace angelica
{
	vector<Symbol> Parser::ParseLineFromInputStream()
	{
		vector<Symbol> symbols;
		
		string line; getline(in_, line);
		for (char ch : line) {
			string symbol;
			symbol = ch;

			if (ch == '|' || ch == ' ') { // 文法的特殊符号
				if (ch == ' ') { // 空格用于分隔产生式的左部和右部。
					symbols.push_back(Symbol(SymbolType::STRUCTURE, symbol));
				}
				if (ch == '|') { // 竖线用于产生式子的缩写
					symbols.push_back(Symbol(SymbolType::STRUCTURE, symbol));
				}
			}
			else if (isupper(ch)) {  // 非终结符
				symbols.push_back(Symbol(SymbolType::NONTERMINAL, symbol));
			} 
			else {  // 终结符
				symbols.push_back(Symbol(SymbolType::TERMINAL, symbol));
			}
		}

		if (!in_.good()) {
			in_.clear();
		} // 尝试恢复状态不良的流。

		return symbols;
	}
}
