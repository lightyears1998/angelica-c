// ll_one_analyzer.h
//
// LL(1)������class LLOneAnalyzer�Ķ���


#pragma once

#include "common.h"

#include <string>
#include <map>
#include <vector>
#include <utility>


namespace angelica
{
	using namespace std;	

	// LL(1)������
	class LLOneAnalyzer
	{
	public:
		LLOneAnalyzer();

		// �����ķ��Ŀ�ʼ����
		void DefineStartSymbol(Symbol symbol);

		// �����﷨����
		void DefineGrammarRule(pair<Symbol, Symbol> line_column_pair, vector<Symbol> right_part);

		// ����﷨����
		void PrintGrammarRules();

		// �Ա����ʽ����﷨����
		void PrintGrammarRulesTable();

		// �ж�һ�������Ƿ�������������ķ�
		bool Judge(vector<Symbol> sequence);

	private:
		
		Symbol start_symbol_;  // �ķ��Ŀ�ʼ����
		map<pair<Symbol, Symbol>, vector<Symbol>> table_;  // ������
	};
}
