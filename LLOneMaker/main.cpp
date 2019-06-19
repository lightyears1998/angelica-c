// main.cpp
//
// LLOneMaker����ڵ㡣

#include "common.h"
#include "parser.h"
#include "ll_one_builder.h"
#include "ll_one_analyzer.h"

#include <iostream>
#include <queue>

using namespace std;
using namespace angelica;


int main()
{
	cout << "����ɽ��Զ�ΪLL(1)�ķ�����ΪLL(1)���������������봮�Ƿ�Ϊ�����ķ��ľ��ӡ�" << endl;
	
	Parser parser(cin);
	LLOneBuilder builder(parser);

	cout << "������LL(1)�ķ���ʹ�ÿո������ķ����󲿺��Ҳ���ÿ������һ������ʽ����Ctrl+Z�������룺" << endl;
	LLOneAnalyzer analyzer = builder.BuildAnalyzer();

	cout << "�����뵥�ʷ��Ŵ����ûس��������룺" << endl;
	vector<Symbol> sentence = parser.ParseLineFromInputStream();
	cout << (analyzer.Judge(sentence) ? "���ʷ��Ŵ��������ķ��ľ��ӡ�" : "���ʷ��Ŵ����������ķ��ľ��ӡ�" ) << endl;
}
