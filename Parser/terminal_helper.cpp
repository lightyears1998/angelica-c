// terminalHelper.cpp
//
// �����������������class TerminalHelper��ʵ�֡�


#include "terminal_helper.h"


namespace angelica
{
	TerminalHelper::TerminalHelper(Parser &parser, istream & in, ostream & out)
		: parser_(parser), in_(in), out_(out)
	{
		// ���õ��ʷ����ڿ���̨���ʱ����ɫ
		colorsheet_[SymbolType::ID] = TerminalColor::BRIGHT_BLUE;
		colorsheet_[SymbolType::STRING] = TerminalColor::BRIGHT_RED;
		colorsheet_[SymbolType::INT] = TerminalColor::BRIGHT_YELLOW;
	}


	void TerminalHelper::InputSourceText()
	{
		out_ << "������Դ���룬��(Ctrl+Z)��Ϊ������־��" << endl;

		string source_text;
		string next_line;
		while (!in_.eof() && getline(in_, next_line))
		{
			source_text += next_line;
			source_text += '\n';
		}
		in_.clear();

		parser_.SetSourceText(source_text);
	}


	void angelica::TerminalHelper::PrintLine(string line)
	{
		out_ << line << endl;
	}


	void angelica::TerminalHelper::PrintSymbol(Symbol symbol, bool show_line_and_column_nubmer)
	{
		TerminalColor terminal_color = getSymbolTypeColor(symbol.type);
		out_ << "(";
		setTextColor(terminal_color); out_ << parser_.GetMnemonicsOfSymbolType(symbol.type);
		resetTextColor();  out_ << ", ";
		setTextColor(terminal_color); out_ << (symbol.value != "" ? symbol.value : "null");
		resetTextColor();
		if (show_line_and_column_nubmer) {
			out_ << ", " << to_string(symbol.line_number) << ":" << to_string(symbol.column_number);
		}
		out_ << ")";
	}


	void angelica::TerminalHelper::PrintSymbols(bool show_line_and_column_nubmer)
	{
		vector<Symbol>& symbols = parser_.GetSymbols();
		for (unsigned index = 0; index < symbols.size(); ++index)
		{
			PrintSymbol(symbols[index], show_line_and_column_nubmer);
			if (index + 1 < symbols.size()) {
				out_ << (symbols[index].line_number != symbols[index + 1].line_number ? '\n' : ' ');
			}
		}
		out_ << '\n';
	}


	void angelica::TerminalHelper::setSymbolTypeColor(SymbolType symbol_type, TerminalColor terminal_color)
	{
		colorsheet_[symbol_type] = terminal_color;
	}

	TerminalColor angelica::TerminalHelper::getSymbolTypeColor(SymbolType symbol_type)
	{
		// �������ɫ���ж����˵��ʷ��Ŷ�Ӧ����ɫ����ô���ظ���ɫ��
		// ���򷵻�Ĭ����ɫ��
		if (colorsheet_.find(symbol_type) != colorsheet_.end())
		{
			return colorsheet_.at(symbol_type);
		}
		return TerminalColor::BRIGHT_WHITE;
	}


	void angelica::TerminalHelper::setTextColor(TerminalColor terminal_color)
	{
		cout << "\x1B[" << to_string(int(terminal_color)) << "m";  // �����Ӧ��ɫ��ANSIת������
	}


	void angelica::TerminalHelper::resetTextColor()
	{
		cout << "\x1B[" << to_string(int(TerminalColor::RESET)) << "m";  // �������ΪĬ����ɫ��ANSIת������
	}
}
