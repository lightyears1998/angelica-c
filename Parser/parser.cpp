#include "parser.h"


namespace angelica
{
	using namespace std;

	Parser::Parser()
	{
		// ��ӹؼ���
		keyword_to_symbol_type_["main"] = SymbolType::KEYWORD_MAIN;
		keyword_to_symbol_type_["int"] = SymbolType::KEYWORD_INT;
		keyword_to_symbol_type_["char"] = SymbolType::KEYWORD_CHAR;
		keyword_to_symbol_type_["if"] = SymbolType::KEYWORD_IF;
		keyword_to_symbol_type_["else"] = SymbolType::KEYWORD_ELSE;
		keyword_to_symbol_type_["for"] = SymbolType::KEYWORD_FOR;
		keyword_to_symbol_type_["while"] = SymbolType::KEYWORD_WHILE;
		keyword_to_symbol_type_["return"] = SymbolType::KEYWORD_RETURN;
		keyword_to_symbol_type_["void"] = SymbolType::KEYWORD_VOID;

		// Ϊ�����ֱ�������Ƿ�
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_MAIN] = "main";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_INT] = "int";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_CHAR] = "char";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_IF] = "if";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_ELSE] = "else";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_FOR] = "for";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_WHILE] = "while";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_RETURN] = "return";
		symbol_type_to_mnemonics_[SymbolType::KEYWORD_VOID] = "void";

		symbol_type_to_mnemonics_[SymbolType::STRING] = "STRING";
		symbol_type_to_mnemonics_[SymbolType::ID] = "ID";
		symbol_type_to_mnemonics_[SymbolType::INT] = "INT";
		symbol_type_to_mnemonics_[SymbolType::EQUALS] = "=";
		symbol_type_to_mnemonics_[SymbolType::PLUS] = "+";
		symbol_type_to_mnemonics_[SymbolType::SUBSTRACT] = "-";
		symbol_type_to_mnemonics_[SymbolType::MULTIPLE] = "*";
		symbol_type_to_mnemonics_[SymbolType::DIVIDE] = "/";
		
		symbol_type_to_mnemonics_[SymbolType::LS_PARENTHESIS] = "(";
		symbol_type_to_mnemonics_[SymbolType::RS_PARENTHESIS] = ")";
		symbol_type_to_mnemonics_[SymbolType::LS_PARENTHESIS] = "[";
		symbol_type_to_mnemonics_[SymbolType::RS_PARENTHESIS] = "]";
		symbol_type_to_mnemonics_[SymbolType::LS_PARENTHESIS] = "{";
		symbol_type_to_mnemonics_[SymbolType::RS_PARENTHESIS] = "}";

		symbol_type_to_mnemonics_[SymbolType::COMMA] = ",";
		symbol_type_to_mnemonics_[SymbolType::COLON] = ":";
		symbol_type_to_mnemonics_[SymbolType::SEMICOLON] = ";";

		symbol_type_to_mnemonics_[SymbolType::RELOP_GT] = ">";
		symbol_type_to_mnemonics_[SymbolType::RELOP_LT] = "<";
		symbol_type_to_mnemonics_[SymbolType::RELOP_GE] = ">=";
		symbol_type_to_mnemonics_[SymbolType::RELOP_LE] = "<=";
		symbol_type_to_mnemonics_[SymbolType::RELOP_EQ] = "==";
		symbol_type_to_mnemonics_[SymbolType::RELOP_NEQ] = "!=";
	}

	void Parser::Parse(string source_code)
	{
		for (size_t idx = 0; idx < source_code.length(); ++idx)
		{
			string token(1, source_code[idx]);  // ��token��ʼ��Ϊinput[idx]

			if (isspace(token[0])) {  // �˳��հ��ַ�
				continue;
			}

			if (isalpha(token[0])) {  // �ؼ��ʻ��ʶ��
				size_t cur = idx + 1;  // �������ĵ�һ���ַ����±�
				while (cur < source_code.length() && (isalpha(source_code[cur]) || isdigit(source_code[cur]))) {
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;
				if (isKeyword(token)) {  // �ؼ���
					SymbolType type = keyword_to_symbol_type_[token];
					symbols_.push_back(Symbol(type, ""));
				}
				else {  // ��ʶ��
					symbols_.push_back(Symbol(SymbolType::ID, token));
				}
				
				continue;
			}

			if (isdigit(token[0])) {  // ������������С����
				size_t cur = idx + 1;
				while (cur < source_code.length() && isdigit(source_code[cur])) {
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;
				symbols_.push_back(Symbol(SymbolType::INT, token));
				continue;
			}

			if (token[0] == '"') {  // �ַ���
				token = "";
				size_t cur = idx + 1;
				while (cur < source_code.length() && source_code[cur] != '"') {  // ������ת���ַ�
					token += source_code[cur];
					cur += 1;
				}

				idx = cur;
				symbols_.push_back(Symbol(SymbolType::STRING, token));
				continue;
			}
		}
	}

	void Parser::defineMnemonicsForSymbolType(SymbolType type, string mnemonics)
	{
		symbol_type_to_mnemonics_[type] = mnemonics;
	}

	void Parser::associateSymbolTypeWithKeyword(SymbolType type, string keyword)
	{
		keyword_to_symbol_type_[keyword] = type;
	}

	bool Parser::isKeyword(string word)
	{
		// ��Ϊ�ؼ��֣�������ڹؼ��ֱ����ҵ��ؼ��ֶ�Ӧ�ĵ����ֱ�
		return keyword_to_symbol_type_.find(word) != keyword_to_symbol_type_.end();
	}

	SymbolType Parser::getKeywordSymbol(string keyword)
	{
		return keyword_to_symbol_type_.at(keyword);
	}

	vector<Symbol>& Parser::GetSymbols()
	{
		return symbols_;
	}

	string Parser::GetSymbolString(Symbol symbol)
	{
		string mnemonics = symbol_type_to_mnemonics_[symbol.type];
		string value = symbol.value != "" ? symbol.value : "null";
		return string("(") + mnemonics + string(", ") + value + string(")");
	}
}
