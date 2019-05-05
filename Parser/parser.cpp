#include "parser.h"


namespace angelica
{
	using namespace std;

	Parser::Parser()
	{
		addKeyword("main", SymbolType::KEYWORD_MAIN);
		addKeyword("int", SymbolType::KEYWORD_INT);
		addKeyword("char", SymbolType::KEYWORD_CHAR);
		addKeyword("if", SymbolType::KEYWORD_IF);
		addKeyword("else", SymbolType::KEYWORD_ELSE);
		addKeyword("for", SymbolType::KEYWORD_FOR);
		addKeyword("while", SymbolType::KEYWORD_WHILE);
		addKeyword("return", SymbolType::KEYWORD_RETURN);
	}

	void Parser::Parse(string source_code)
	{
		for (size_t idx = 0; idx < source_code.length(); ++idx)
		{
			string token(1, source_code[idx]);  // ��token��ʼ��Ϊinput[idx]

			if (isspace(token[0])) {  // �˳��հ��ַ�
				continue;
			}

			if (isalpha(token[0])) {
				size_t cur = idx + 1;  // �������ĵ�һ���ַ����±�
				while (cur < source_code.length() && (isalpha(source_code[cur]) || isdigit(source_code[cur]))) {
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;
				symbols_.push_back(Symbol(SymbolType::ID, token));  // ����Ҫ�����Ƿ�Ϊ�ؼ���
				continue;
			}

			if (isdigit(token[0])) {
				size_t cur = idx + 1;
				while (cur < source_code.length() && isdigit(source_code[cur])) {
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;
				symbols_.push_back(Symbol(SymbolType::INT, token));
				continue;
			}

			if (token[0] == '"') {
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

	bool Parser::IsKeyword(string word)
	{
		// ��Ϊ�ؼ��֣�������ڹؼ��ֱ����ҵ��ؼ��ֶ�Ӧ�ĵ����ֱ�
		return keyword_to_symbol_type_.find(word) != keyword_to_symbol_type_.end();
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

	void Parser::addKeyword(string keyword, SymbolType type)
	{
		keyword_to_symbol_type_[keyword] = type;
		symbol_type_to_keyword_[type] = keyword;
		symbol_type_to_mnemonics_[type] = keyword;
	}
}
