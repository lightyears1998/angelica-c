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

			if (ch == '|' || ch == ' ') { // �ķ����������
				if (ch == ' ') { // �ո����ڷָ�����ʽ���󲿺��Ҳ���
					symbols.push_back(Symbol(SymbolType::STRUCTURE, symbol));
				}
				if (ch == '|') { // �������ڲ���ʽ�ӵ���д
					symbols.push_back(Symbol(SymbolType::STRUCTURE, symbol));
				}
			}
			else if (isupper(ch)) {  // ���ս��
				symbols.push_back(Symbol(SymbolType::NONTERMINAL, symbol));
			} 
			else {  // �ս��
				symbols.push_back(Symbol(SymbolType::TERMINAL, symbol));
			}
		}

		if (!in_.good()) {
			in_.clear();
		} // ���Իָ�״̬����������

		return symbols;
	}
}
