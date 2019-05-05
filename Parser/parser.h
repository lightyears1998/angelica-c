#pragma once

#include "common.h"

#include <string>
#include <vector>
#include <map>


namespace angelica
{
	using namespace std;

	// �ʷ�������
	class Parser
	{
	public:
		Parser();
		
		// ��ָ��souce_code���дʷ�����
		void Parse(string source_code);

		// ���ر��浥�ʷ��ŵ�����
		vector<Symbol>& GetSymbols();

		// ���ص��ʷ��ŵ��ַ�����ʾ
		string GetSymbolString(Symbol symbol);

	private:
		// ���嵥�ʷ����ֱ�����Ƿ�
		void defineMnemonicsForSymbolType(SymbolType type, string mnemonics);
		
		// �������ʷ����ֱ���ؼ���
		void associateSymbolTypeWithKeyword(SymbolType type, string keyword);

		// �ж�word�Ƿ�Ϊ�ؼ���
		bool isKeyword(string word);

		// ���عؼ��ʶ�Ӧ�ĵ��ʷ����ֱ�
		SymbolType getKeywordSymbol(string keyword);

		vector<Symbol> symbols_;  // ���Ա��浥�ʷ��ŵ�����
		map<string, SymbolType> keyword_to_symbol_type_;  // ����ؼ��ʶ�Ӧ�ĵ��ʷ����ֱ�
		map<SymbolType, string> symbol_type_to_mnemonics_;  // ���浥�ʷ����ֱ��Ӧ�����Ƿ�
	};
}
