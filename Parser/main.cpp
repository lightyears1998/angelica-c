// main.cpp
//
// �ʷ������Ĳ��Ե�Ԫ��


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

	helper.InputSourceText();  // ������������Դ����
	
	parser.Parse();  // ���дʷ�����

	bool show_column_and_line_nubmer = true;
	helper.PrintSymbols(show_column_and_line_nubmer);  // ��ӡ�Ѿ������ĵ��ʷ���
}
