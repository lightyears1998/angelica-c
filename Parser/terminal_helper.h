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

	// 定义在终端中显示的颜色
	enum class TerminalColor : int
	{
		RESET           = 0 ,  // 枚举的值是对应ANSI颜色转义字符的值
		BRIGHT_BLACK    = 90,
		BRIGHT_RED      = 91,
		BRIGHT_GREEN    = 92,
		BRIGHT_YELLOW   = 93,
		BRIGHT_BLUE     = 94,
		BRIGHT_MAGENTA  = 95,
		BRIGHT_CYAN     = 96,
		BRIGHT_WHITE    = 97,
	};


	// 从终端进行输入输出时的辅助类
	class TerminalHelper
	{
	public:
		// 使用指定的输入流和输出流创建TerminalHelper对象
		// 输入流和输出流通常为cin和cout
		TerminalHelper(Parser &parser, istream &in, ostream &out);

		// 从输入流中读取源代码
		void InputSourceText();
		
		// 向输出流中打印一行
		void PrintLine(string line);

		// 输出字符串形式的单词符号到输出流
		void PrintSymbol(Symbol symbol, bool show_line_and_column_nubmer = false);

		// 输出字符串形式的单词符号到输出流
		void PrintSymbols(bool show_line_and_column_nubmer = false);

	private:
		Parser &parser_;
		istream &in_;
		ostream &out_;
		map<SymbolType, TerminalColor> colorsheet_;

		void setSymbolTypeColor(SymbolType symbol_type, TerminalColor terminal_color);
		TerminalColor getSymbolTypeColor(SymbolType symbol_type);

		// 设置控制台文本颜色
		void setTextColor(TerminalColor terminal_color);

		// 重置输出颜色为默认
		void resetTextColor();
	};
}