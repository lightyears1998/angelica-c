// commom.h
//
// ���嵥�ʷ��ŵ��ֱ�enum SymbolType��
// �Լ����ʷ���struct Symbol��


#pragma once

#include <string>


namespace angelica
{
	using namespace std;

	// ���ʷ��ŵ��ֱ�
	enum class SymbolType : int
	{
		TERMINAL, NONTERMINAL, STRUCTURE
	};

	// ���ʷ���
	struct Symbol
	{
		SymbolType type;  // ���ʷ����ֱ�
		string value;     // ���ʷ��ŵ�ֵ
		unsigned line_number, column_number;  // ���ڵ��кź��к�


		Symbol(SymbolType symbol_type, string value, unsigned line_number, unsigned column_number) :
			type(symbol_type), value(value), line_number(line_number), column_number(column_number)
		{};
	};
}
