// main.cpp
// 
// ���﷨��������SimpleAnalyzer������ڵ㡣


#include "ll_one_analyzer.h"

#include <iostream>
#include <vector>


using namespace std;
using namespace angelica;


// �ж����봮�Ƿ�Ϊ�����ķ��ľ���
void UseAnalyzerToJudge(LLOneAnalyzer& analyzer, vector<Symbol> input)
{
	string input_string;
	for (auto symbol : input) input_string += symbol;

	cout << "���봮��" << input_string << endl;

	bool input_is_sentence = analyzer.Judge(input);
	
	cout << "���봮" << input_string;
	cout << (input_is_sentence ? "��" : "����");
	cout << "�����ķ��ľ��ӡ�" << endl;
	cout << endl;
}


// ���ڴ�ʵ�����ݽ�Ϊ�򵥣�main����Ҳ�����ʷ��������Ĺ��ܡ�
int main()
{
	LLOneAnalyzer analyzer;
	
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "i", "+", "i" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "i", "+", "(", "i" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "i", "+", "i", ")" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "(", "*", ")" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "(", "+", "i" });
}
