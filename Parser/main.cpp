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

	string input = helper.InputSourceText();

	// 进行词法分析
	parser.Parse(input);
	helper.PrintSymbols(parser.GetSymbols());
}
