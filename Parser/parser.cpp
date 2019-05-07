#include "parser.h"


namespace angelica
{
	using namespace std;

	Parser::Parser()
	{
		// ��ӹؼ���
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_MAIN, "main");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_INT, "int");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_CHAR, "char");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_IF, "if");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_ELSE, "else");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_FOR, "for");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_WHILE, "while");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_RETURN, "return");
		associateSymbolTypeWithKeyword(SymbolType::KEYWORD_VOID, "void");

		// Ϊ�����ֱ�������Ƿ�
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_MAIN, "main");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_INT, "int");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_CHAR, "char");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_IF, "if");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_ELSE, "else");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_FOR, "for");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_WHILE, "while");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_RETURN, "return");
		defineMnemonicsForSymbolType(SymbolType::KEYWORD_VOID, "void");
		
		defineMnemonicsForSymbolType(SymbolType::STRING, "STRING");
		defineMnemonicsForSymbolType(SymbolType::ID, "ID");
		defineMnemonicsForSymbolType(SymbolType::INT, "INT");
		defineMnemonicsForSymbolType(SymbolType::ASSIGNMENT, "=");
		defineMnemonicsForSymbolType(SymbolType::PLUS, "+");
		defineMnemonicsForSymbolType(SymbolType::SUBSTRACT, "-");
		defineMnemonicsForSymbolType(SymbolType::MULTIPLE, "*");
		defineMnemonicsForSymbolType(SymbolType::DIVIDE, "/");

		defineMnemonicsForSymbolType(SymbolType::LS_PARENTHESIS, "(");
		defineMnemonicsForSymbolType(SymbolType::RS_PARENTHESIS, ")");
		defineMnemonicsForSymbolType(SymbolType::LM_PARENTHESIS, "[");
		defineMnemonicsForSymbolType(SymbolType::RM_PARENTHESIS, "]");
		defineMnemonicsForSymbolType(SymbolType::LL_PARENTHESIS, "{");
		defineMnemonicsForSymbolType(SymbolType::RL_PARENTHESIS, "}");

		defineMnemonicsForSymbolType(SymbolType::COMMA, ",");
		defineMnemonicsForSymbolType(SymbolType::COLON, ":");
		defineMnemonicsForSymbolType(SymbolType::SEMICOLON, ";");

		defineMnemonicsForSymbolType(SymbolType::RELOP_GT, ">");
		defineMnemonicsForSymbolType(SymbolType::RELOP_LT, "<");
		defineMnemonicsForSymbolType(SymbolType::RELOP_GE, ">=");
		defineMnemonicsForSymbolType(SymbolType::RELOP_LE, "<=");
		defineMnemonicsForSymbolType(SymbolType::RELOP_EQ, "==");
		defineMnemonicsForSymbolType(SymbolType::RELOP_NEQ, "!=");
	}

	void Parser::Parse(string source_code)
	{
		symbols_.clear();  // �ڴʷ�������ʼǰ����ձ��浥�ʷ��ŵ�����

		for (size_t idx = 0; idx < source_code.length(); ++idx)
		{
			string token;  // ���ڱ��浥�ʷ��ŵ��ַ���
			token = source_code[idx];  // ��token��ʼ��Ϊinput[idx]

			if (isspace(token[0])) {  // �˳��հ��ַ�
				continue;
			}

			if (token[0] == '=') { // ʶ��Ϊ��=����==��
				if (idx + 1 < source_code.length() && source_code.substr(idx, 2) == "==")
				{  // ��==��
					symbols_.push_back(Symbol(SymbolType::RELOP_EQ, ""));
				}
				else
				{  // ��=��
					symbols_.push_back(Symbol(SymbolType::ASSIGNMENT, ""));
				}

				continue;
			}

			if (token[0] == '+') {  // ��+��
				symbols_.push_back(Symbol(SymbolType::PLUS, ""));
				continue;
			}

			if (token[0] == '-') {  // ��-��
				symbols_.push_back(Symbol(SymbolType::SUBSTRACT, ""));
				continue;
			}

			if (token[0] == '*') {  // ��*��
				symbols_.push_back(Symbol(SymbolType::MULTIPLE, ""));
				continue;
			}

			if (token[0] == '/') {  // ��//������/*����/��
				if (idx + 1 < source_code.length())
				{
					if (source_code[idx + 1] == '/')
					{  // ��//��
						++idx;
						while (idx < source_code.length() && source_code[idx] != '\n') 
							++idx;  // �˳�ע��

						continue;
					}
					else
					{  // ��/*��
						++idx;
						while (idx + 1 < source_code.length() && source_code.substr(idx, 2) != "*/")
							++idx;  // �˳�ע��
						
						continue;
					}
				}
				else
				{  // ��/��
					symbols_.push_back(Symbol(SymbolType::DIVIDE, ""));

					continue;
				}
			}

			if (token[0] == '(') {  // ��(��
				symbols_.push_back(Symbol(SymbolType::LS_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == ')') {  // ��)��
				symbols_.push_back(Symbol(SymbolType::RS_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == '[') {  // ��[��
				symbols_.push_back(Symbol(SymbolType::LM_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == ']') {  // ��]��
				symbols_.push_back(Symbol(SymbolType::RM_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == '{') {  // ��{��
				symbols_.push_back(Symbol(SymbolType::LL_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == '}') {  // ��}��
				symbols_.push_back(Symbol(SymbolType::RL_PARENTHESIS, ""));
				continue;
			}

			if (token[0] == ',') {  // ��,��
				symbols_.push_back(Symbol(SymbolType::COMMA, ""));
				continue;
			}

			if (token[0] == ':') {  // ��:��
				symbols_.push_back(Symbol(SymbolType::COLON, ""));
				continue;
			}

			if (token[0] == ';') {  // ��;��
				symbols_.push_back(Symbol(SymbolType::SEMICOLON, ""));
				continue;
			}

			if (isalpha(token[0]) || token[0] == '_') {  // ʶ��Ϊ�ؼ��ʻ��ʶ��
				size_t cur = idx + 1;  // �������ĵ�һ���ַ����±�
				while (cur < source_code.length() && (isalpha(source_code[cur]) || isdigit(source_code[cur]) || source_code[cur] == '_')) 
				{
					token += source_code[cur];
					cur += 1;
				}

				idx = cur - 1;  // ����һ���ַ�
				if (isKeyword(token)) {  // ʶ��Ϊ�ؼ���
					SymbolType type = keyword_to_symbol_type_[token];
					symbols_.push_back(Symbol(type, ""));
				}
				else {  // ʶ��Ϊ��ʶ��
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

			if (token[0] == '>')  // ��>������>=��
			{
				if (idx + 1 < source_code.length() && source_code[idx + 1] == '=')
				{
					symbols_.push_back(Symbol(SymbolType::RELOP_GE, ""));
					++idx;
					continue;
				}

				symbols_.push_back(Symbol(SymbolType::RELOP_GT, ""));
				continue;
			}

			if (token[0] == '<')  // ��<������<=��
			{
				if (idx + 1 < source_code.length() && source_code[idx + 1] == '=')
				{
					symbols_.push_back(Symbol(SymbolType::RELOP_LE, ""));
					++idx;
					continue;
				}

				symbols_.push_back(Symbol(SymbolType::RELOP_LT, ""));
				continue;
			}

			if (token[0] == '=')  // ��=������==��
			{
				if (idx + 1 < source_code.length() && source_code[idx + 1] == '=')
				{
					symbols_.push_back(Symbol(SymbolType::RELOP_EQ, ""));
					++idx;
					continue;
				}
				
				symbols_.push_back(Symbol(SymbolType::ASSIGNMENT, ""));
				continue;
			}

			if (token[0] == '!' && idx + 1 < source_code.length() && source_code[idx+1] == '=')  // ��!=��
			{  // ʶ��Ϊ��!=��
				symbols_.push_back(Symbol(SymbolType::RELOP_NEQ, ""));
				++idx;
				continue;
			}

			// ���û�б��κ�һ��if��䲶׽����Ӧ�ñ������
			throw new exception("�������ݲ��ϴʷ���");
		}
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

	SymbolType Parser::getSymbolOfKeyword(string keyword)
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
