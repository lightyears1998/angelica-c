// main.cpp
//
// 词法分析的测试单元。


#include "parser.h"
#include "terminal_helper.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace angelica;


// 从标准输入中读取源代码，并输出单词符号
int main()
{	
	Parser parser;
	TerminalHelper helper(parser, cin, cout);

	helper.InputSourceText();  // 从命令行输入源代码
	
	parser.Parse();  // 进行词法分析

	bool show_column_and_line_nubmer = true;
	helper.PrintSymbols(show_column_and_line_nubmer);  // 打印已经分析的单词符号
}
