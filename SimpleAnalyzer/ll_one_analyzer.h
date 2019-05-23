// ll_one_analyzer.h
//
// LL(1)������class LLOneAnalyzer�Ķ���


#pragma once

#include "common.h"

#include <string>
#include <map>
#include <utility>


namespace angelica
{
	// LL(1)������
	class LLOneAnalyzer
	{
	public:
		LLOneAnalyzer();

		// �����﷨����
		void DefineGrammarSymbol(string mark, GrammarSymbolType type);

		// �����ķ��Ŀ�ʼ����
		void DefineStartSymbol(string mark);

		// �����﷨����
		void DefineGrammarRule(pair<string, string> line_column_pair, pair<string, string> left_right_part_pair);

	private:
		// ȡ��ĳ���﷨���ŵ�����
		GrammarSymbolType getGrammarSymbolType(string mark);
		
		string start_symbol_;                                    // �ķ��Ŀ�ʼ����
		map<string, GrammarSymbolType> symbols_;                 // �﷨���ű�
		map<pair<string, string>, pair<string, string>> table_;  // ������
	};
}
