#include "parser.h"
#include "terminal_helper.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace angelica;


// �ӱ�׼�����ж�ȡԴ���룬��������ʷ���
int main()
{	
	Parser parser;
	TerminalHelper helper(parser, cin, cout);

	string input = helper.InputSourceText();

	// ���дʷ�����
	parser.Parse(input);
	helper.PrintSymbols(parser.GetSymbols());
}
