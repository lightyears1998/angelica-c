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
		EQUALS = 21,  // �Ⱥ�
		PLUS, SUBSTRACT, MINUS, DIVIDE,
		LS_PARENTHESIS, RS_PARENTHESIS, // ��С���ţ���С����
		LM_PARENTHESIS, RM_PARENTHESIS,
		LL_PARENTHESIS, RL_PARENTHESIS,
		COMMA, COLON, SEMICOLON,  // ���ţ�ð�ţ��ֺ�
		RELOP_GT, RELOP_LT, RELOP_GE, RELOP_LE, RELOP_EQ, RELOP_NEQ
	};

	// ���ʷ���
	class Symbol
	{
	public:
		Symbol(SymbolType type);
		Symbol(SymbolType type, string value);

		string ToString();

	private:
		SymbolType type_;
		string value_;
	};
}
