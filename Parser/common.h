#pragma once

#include <string>


namespace angelica
{
	using namespace std;

	// µ¥´Ê·ûºÅµÄÖÖ±ð
	enum class SymbolType : int
	{
		KEYWORD_MAIN = 1,
		KEYWORD_INT, KEYWORD_CHAR, KEYWORD_IF, KEYWORD_ELSE,
		KEYWORD_FOR, KEYWORD_WHILE, KEYWORD_RETURN,
		KEYWORD_VOID,
		STRING = 50, ID = 10, INT = 20,
		EQUALS = 21,  // µÈºÅ
		PLUS, SUBSTRACT, MULTIPLE, DIVIDE,
		LS_PARENTHESIS, RS_PARENTHESIS, // ×óÐ¡À¨ºÅ£¬ÓÒÐ¡À¨ºÅ
		LM_PARENTHESIS, RM_PARENTHESIS,
		LL_PARENTHESIS, RL_PARENTHESIS,
		COMMA, COLON, SEMICOLON,  // ¶ººÅ£¬Ã°ºÅ£¬·ÖºÅ
		RELOP_GT, RELOP_LT, RELOP_GE, RELOP_LE, RELOP_EQ, RELOP_NEQ
	};

	// µ¥´Ê·ûºÅ
	struct Symbol
	{
		SymbolType type;
		string value;

		Symbol(SymbolType type) : type(type) {};
		Symbol(SymbolType type, string value) : type(type), value(value) {};
	};
}
