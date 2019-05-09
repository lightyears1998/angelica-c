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

	void Parser::Parse()
	{
		while (current_index_ < source_text_.length())
		{
			string token;  // ���ڱ��浥�ʷ��ŵ��ַ���
			token = source_text_[current_index_];  // ��token��ʼ��Ϊ�������ĵ�һ���ַ�

			if (isspace(token[0])) {  // �˳��հ��ַ�
				if (token[0] == '\n') {
					++current_index_;
					++line_number_, column_number_ = 1;
				}
				else {
					++current_index_;
					++column_number_;
				}
				continue;
			}

			if (token[0] == '=') { // ʶ��Ϊ��=����==��
				if (current_index_ + 1 < source_text_.length() && source_text_.substr(current_index_, 2) == "==")
				{  // ��==��
					collectSymbol(SymbolType::RELOP_EQ, "");
					current_index_ += 2;
					column_number_ += 2;
				}
				else
				{  // ��=��
					collectSymbol(SymbolType::ASSIGNMENT, "");
					current_index_ += 1;
					column_number_ += 1;
				}
				continue;
			}

			if (token[0] == '+') {  // ��+��
				collectSymbol(SymbolType::PLUS, "");
				++current_index_;
				++column_number_;
				continue;
			}

			if (token[0] == '-') {  // ��-��
				collectSymbol(SymbolType::SUBSTRACT, "");
				++current_index_;
				++column_number_;
				continue;
			}

			if (token[0] == '*') {  // ��*��
				collectSymbol(SymbolType::MULTIPLE, "");
				++current_index_;
				++column_number_;
				continue;
			}

			if (token[0] == '/') {  // ��//������/*����/��
				if (current_index_ + 1 < source_text_.length())
				{
					if (source_text_[current_index_ + 1] == '/')
					{  // ��//��
						current_index_ += 2;
						while (current_index_ < source_text_.length() && source_text_[current_index_] != '\n')
							++current_index_;  // �˳�ע��
						++current_index_;
						++line_number_, column_number_ = 1;
						continue;
					}
					else if (source_text_[current_index_ + 1] == '*')
					{  // ��/*��
						current_index_ += 2, column_number_ += 2;
						while (current_index_ + 1 < source_text_.length() && source_text_.substr(current_index_, 2) != "*/")
						{
							++current_index_;
							if (source_text_[current_index_] != '\n') {
								++column_number_;
							}
							else {
								++line_number_, column_number_ = 1;
							}
						}
						current_index_ += 2, column_number_ += 2;
						continue;
					}
				}
				else
				{  // ��/��
					collectSymbol(SymbolType::DIVIDE, "");
					++current_index_, ++column_number_;
					continue;
				}
			}

			if (token[0] == '(') {  // ��(��
				collectSymbol(SymbolType::LS_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ')') {  // ��)��
				collectSymbol(SymbolType::RS_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == '[') {  // ��[��
				collectSymbol(SymbolType::LM_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ']') {  // ��]��
				collectSymbol(SymbolType::RM_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == '{') {  // ��{��
				collectSymbol(SymbolType::LL_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == '}') {  // ��}��
				collectSymbol(SymbolType::RL_PARENTHESIS, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ',') {  // ��,��
				collectSymbol(SymbolType::COMMA, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ':') {  // ��:��
				collectSymbol(SymbolType::COLON, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (token[0] == ';') {  // ��;��
				collectSymbol(SymbolType::SEMICOLON, "");
				++current_index_, ++column_number_;
				continue;
			}

			if (isalpha(token[0]) || token[0] == '_') {  // �ؼ��ʻ��ʶ������ĸ���»��߿�ͷ
				unsigned end_of_identifier_index = current_index_ + 1;  // �ؼ��ֻ��־�����һ���ַ���Դ�����е��±�
				while (end_of_identifier_index < source_text_.length() && isLegalIdentifierCharacter(source_text_[end_of_identifier_index]))
				{
					token += source_text_[end_of_identifier_index];
					++end_of_identifier_index;
				}
				--end_of_identifier_index;  // ����һ���ַ�
				if (isKeyword(token)) {  // ʶ��Ϊ�ؼ���
					collectSymbol(getSymbolOfKeyword(token) , "");
				}
				else {  // ʶ��Ϊ��ʶ��
					collectSymbol(SymbolType::ID, token);
				}
				column_number_ += end_of_identifier_index - current_index_ + 1;
				current_index_ = end_of_identifier_index + 1;
				continue;
			}

			if (isdigit(token[0])) {  // ������������С����
				unsigned end_of_number_index = current_index_ + 1;
				while (end_of_number_index < source_text_.length() && isdigit(source_text_[end_of_number_index])) {
					token += source_text_[end_of_number_index];
					++end_of_number_index;
				}
				--end_of_number_index;  // ����һ���ַ�
				collectSymbol(SymbolType::INT, token);
				column_number_ += end_of_number_index - current_index_ + 1;
				current_index_ = end_of_number_index + 1;
				continue;
			}

			if (token[0] == '"') {  // �ַ���
				token = "";
				unsigned end_of_string_index = current_index_ + 1;
				while (end_of_string_index < source_text_.length() && source_text_[end_of_string_index] != '"') {  // ������ת���ַ�
					token += source_text_[end_of_string_index];
					end_of_string_index += 1;
				}
				collectSymbol(SymbolType::STRING, token);
				column_number_ += end_of_string_index - current_index_ + 1;
				current_index_ = end_of_string_index + 1;
				continue;
			}

			if (token[0] == '>')  // ��>������>=��
			{
				if (current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // ��>=��
				{
					collectSymbol(SymbolType::RELOP_GE, "");
					current_index_ += 2, column_number_ += 2;
					continue;
				}
				else {
					collectSymbol(SymbolType::RELOP_GT, "");
					++current_index_, ++column_number_;
					continue;
				}
			}

			if (token[0] == '<')  // ��<������<=��
			{
				if (current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // ��<=��
				{
					collectSymbol(SymbolType::RELOP_LE, "");
					current_index_ += 2, column_number_ += 2;
					continue;
				}
				else {  // ��<��
					collectSymbol(SymbolType::RELOP_LT, "");
					++current_index_, ++column_number_;
					continue;
				}
			}

			if (token[0] == '=')  // ��=������==��
			{
				if (current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // ��==��
				{
					collectSymbol(SymbolType::RELOP_EQ, "");
					current_index_ += 2, column_number_ += 2;
					continue;
				}
				else {  // ��=��
					collectSymbol(SymbolType::ASSIGNMENT, "");
					++current_index_, ++column_number_;
				}
				
				continue;
			}

			if (token[0] == '!' && current_index_ + 1 < source_text_.length() && source_text_[current_index_ + 1] == '=')  // ��!=��
			{  // ʶ��Ϊ��!=��
				collectSymbol(SymbolType::RELOP_NEQ, "");
				++current_index_ += 2, column_number_ += 2;
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

	bool Parser::isLegalIdentifierCharacter(char character)
	{
		return isalpha(character) || isdigit(character) || character == '_';
	}

	SymbolType Parser::getSymbolOfKeyword(string keyword)
	{
		return keyword_to_symbol_type_.at(keyword);
	}

	void Parser::collectSymbol(SymbolType symbol_type, string value)
	{
		symbols_.push_back(Symbol(symbol_type, value, line_number_, column_number_));
	}

	vector<Symbol>& Parser::GetSymbols()
	{
		return symbols_;
	}

	void Parser::SetSourceText(string source_text)
	{
		source_text_ = source_text;
		current_index_ = 0;
		line_number_ = 1, column_number_ = 1;
		symbols_.clear();
	}

	string Parser::GetMnemonicsOfSymbolType(SymbolType symbol_type)
	{
		return symbol_type_to_mnemonics_[symbol_type];
	}
}
