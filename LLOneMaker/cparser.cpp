#include "cparser.h"

using namespace std;


namespace angelica
{
	CParser::CParser()
	{

		// Ϊ�ķ���ӹؼ���
		associateSymbolTypeWithKeyword(SymbolType::STRUCTURE, "��");
		associateSymbolTypeWithKeyword(SymbolType::STRUCTURE, "|");


	}


	// ��д���ຯ��
	void CParser::Parse()
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

			else {  // �ؼ��ʻ��ʶ��  ���ǿո�
				unsigned end_of_identifier_index = current_index_ + 1;  // �ؼ��ֻ��־�����һ���ַ���Դ�����е��±�
				while (end_of_identifier_index < source_text_.length() && isLegalIdentifierCharacter(source_text_[end_of_identifier_index]))
				{
					token += source_text_[end_of_identifier_index];
					++end_of_identifier_index;
				}
				--end_of_identifier_index;  // ����һ���ַ�
				
				
				if (token >= "A" && token <= "Z") {
					associateSymbolTypeWithKeyword(SymbolType::NONTERMINAL, token);
				}
				else if (token == "��" || token == "|") {
					associateSymbolTypeWithKeyword(SymbolType::STRUCTURE, token);
				}
				else
					associateSymbolTypeWithKeyword(SymbolType::TERMINAL, token);

				column_number_ += end_of_identifier_index - current_index_ + 1;
				current_index_ = end_of_identifier_index + 1;
				continue;
			}
		}
	}
}
