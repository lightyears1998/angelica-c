#include "cparser.h"

using namespace std;


namespace angelica
{
	CParser::CParser()
	{

		// 为文法添加关键词
		associateSymbolTypeWithKeyword(SymbolType::STRUCTURE, "→");
		associateSymbolTypeWithKeyword(SymbolType::STRUCTURE, "|");


	}


	// 重写基类函数
	void CParser::Parse()
	{
		while (current_index_ < source_text_.length())
		{
			string token;  // 用于保存单词符号的字符串
			token = source_text_[current_index_];  // 将token初始化为待分析的第一个字符

			if (isspace(token[0])) {  // 滤除空白字符
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

			else {  // 关键词或标识符  不是空格
				unsigned end_of_identifier_index = current_index_ + 1;  // 关键字或标志符最后一个字符在源代码中的下标
				while (end_of_identifier_index < source_text_.length() && isLegalIdentifierCharacter(source_text_[end_of_identifier_index]))
				{
					token += source_text_[end_of_identifier_index];
					++end_of_identifier_index;
				}
				--end_of_identifier_index;  // 回退一个字符
				
				
				if (token >= "A" && token <= "Z") {
					associateSymbolTypeWithKeyword(SymbolType::NONTERMINAL, token);
				}
				else if (token == "→" || token == "|") {
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
