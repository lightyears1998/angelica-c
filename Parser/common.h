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
		KEYWORD_MAIN = 1,
		KEYWORD_INT, KEYWORD_CHAR, KEYWORD_IF, KEYWORD_ELSE,
		KEYWORD_FOR, KEYWORD_WHILE, KEYWORD_RETURN,
		KEYWORD_VOID,
		STRING = 50, ID = 10, INT = 20,
		ASSIGNMENT = 21,  // ��ֵ���š�=��
		PLUS, SUBSTRACT, MULTIPLE, DIVIDE,
		LS_PARENTHESIS, RS_PARENTHESIS, // ��С���ţ���С����
		LM_PARENTHESIS, RM_PARENTHESIS,
		LL_PARENTHESIS, RL_PARENTHESIS,
		COMMA, COLON, SEMICOLON,  // ���ţ�ð�ţ��ֺ�
		RELOP_GT, RELOP_LT, RELOP_GE, RELOP_LE, RELOP_EQ, RELOP_NEQ
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