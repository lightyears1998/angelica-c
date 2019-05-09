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

		// ���ô�������Դ����
		void SetSourceText(string source_text);

		// �Ե�ǰָ����Դ������дʷ�����
		void Parse();

		// ���ر��浥�ʷ��ŵ�����
		vector<Symbol>& GetSymbols();

		// ��ȡ���ʷ������͵����Ƿ�
		string GetMnemonicsOfSymbolType(SymbolType symbol_type);

	private:
		// ���嵥�ʷ����ֱ�����Ƿ�
		void defineMnemonicsForSymbolType(SymbolType symbol_type, string mnemonics);
		
		// �������ʷ����ֱ���ؼ���
		void associateSymbolTypeWithKeyword(SymbolType symbol_type, string keyword);

		// �ж�word�Ƿ�Ϊ�ؼ���
		bool isKeyword(string word);

		// �ж�character�Ƿ�Ϊ�Ϸ��ı�ʶ���ַ�
		bool isLegalIdentifierCharacter(char character);

		// ���عؼ��ʶ�Ӧ�ĵ��ʷ����ֱ�
		SymbolType getSymbolOfKeyword(string keyword);

		// �������õ��ĵ��ʷ��ű��浽������
		void collectSymbol(SymbolType symbol_type, string value);


		string source_text_;                    // Դ����
		unsigned current_index_;                // Դ��������һ�����������ַ����±�
		unsigned line_number_, column_number_;  // Դ�����е�current_idx��ָ���ַ����кź��к�

		vector<Symbol> symbols_;  // ���Ա��浥�ʷ��ŵ�����

		map<string, SymbolType> mnemonics_to_symbol_type_;  // �������Ƿ���Ӧ�ĵ��ʷ����ֱ�
		map<string, SymbolType> keyword_to_symbol_type_;    // ����ؼ��ʶ�Ӧ�ĵ��ʷ����ֱ�
		map<SymbolType, string> symbol_type_to_mnemonics_;  // ���浥�ʷ����ֱ��Ӧ�����Ƿ�
		map<SymbolType, string> symbol_type_to_keyword_;    // ���浥�ʷ����ֱ��Ӧ�Ĺؼ���
	};
}
