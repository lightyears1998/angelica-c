// ll_one_builder.h
//
// LL(1)�������������Ķ��塣

#pragma once

#include "common.h"
#include "parser.h"
#include "ll_one_analyzer.h"

#include <set>
#include <map>
#include <functional>

namespace angelica {
	// LL(1)������������
	// ���Զ����ɷ���LL(1)����ķ�������
	class LLOneBuilder
	{
	private:
		Parser parser_;                             // �����ķ�ʹ�õĴʷ�������

		LLOneAnalyzer analyzer;                     // �������ķ���Ӧ�ķ�����
		set<Symbol> nonterminal_set;                // �������з��ս���ļ���
		Symbol start_symbol;                        // �����ķ��Ŀ�ʼ����
		map<Symbol, vector<Symbol>> left_to_right;  // �󲿷��ս�����Ҳ����ŵ�ӳ��

	public:
		LLOneBuilder(Parser &parser) : parser_(parser) {};

		// ��Parser�л�ȡ��ʾLL(1)�ķ��ķ��ţ������ض�Ӧ�ķ���LL(1)��������
		LLOneAnalyzer BuildAnalyzer();

	private:
		// ��Parser�л�ȡ�ķ�����
		void getInputFromParser();
		
		// ������ݹ�
		void diminishLeftRecursion();

		// ��������
		void removeLookBack();

		// ��ȡһ���ս���������Ƶ����ĵ�һ�����ս���ļ��ϣ�First����
		set<Symbol> getPossibleFirstTerminalSymbol(Symbol left);

		// ��ȡһ���ս��֮���������Ƶ����ĵ�һ�����ս���ļ��ϣ�Follow����
		set<Symbol> getPossibleFollowTerminalSymbol(Symbol left);

		// ��ӡ���ս������
		void printNonterminalSymbolSet();
	
		// ��ӡFirst��
		void printFirstSet();

		// ��ӡFollow��
		void printFollowSet();

		// �����ķ���Ӧ�ķ�����
		void buildAnalyzer();
	};
}
