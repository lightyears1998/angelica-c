#pragma once

#include "common.h"
#include "parser.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>


namespace angelica
{
	using namespace std;

	// �������ն�����ʾ����ɫ
	enum class TerminalColor : int
	{
		RESET           = 0 ,  // ö�ٵ�ֵ�Ƕ�ӦANSI��ɫת���ַ���ֵ
		BRIGHT_BLACK    = 90,
		BRIGHT_RED      = 91,
		BRIGHT_GREEN    = 92,
		BRIGHT_YELLOW   = 93,
		BRIGHT_BLUE     = 94,
		BRIGHT_MAGENTA  = 95,
		BRIGHT_CYAN     = 96,
		BRIGHT_WHITE    = 97,
	};


	// ���ն˽����������ʱ�ĸ�����
	class TerminalHelper
	{
	public:
		// ʹ��ָ���������������������TerminalHelper����
		// �������������ͨ��Ϊcin��cout
		TerminalHelper(Parser &parser, istream &in, ostream &out);

		// ���������ж�ȡԴ����
		void InputSourceText();
		
		// ��������д�ӡһ��
		void PrintLine(string line);

		// ����ַ�����ʽ�ĵ��ʷ��ŵ������
		void PrintSymbol(Symbol symbol, bool show_line_and_column_nubmer = false);

		// ����ַ�����ʽ�ĵ��ʷ��ŵ������
		void PrintSymbols(bool show_line_and_column_nubmer = false);

	private:
		Parser &parser_;
		istream &in_;
		ostream &out_;
		map<SymbolType, TerminalColor> colorsheet_;

		void setSymbolTypeColor(SymbolType symbol_type, TerminalColor terminal_color);
		TerminalColor getSymbolTypeColor(SymbolType symbol_type);

		// ���ÿ���̨�ı���ɫ
		void setTextColor(TerminalColor terminal_color);

		// ���������ɫΪĬ��
		void resetTextColor();
	};
}