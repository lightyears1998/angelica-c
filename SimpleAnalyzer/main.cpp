// main.cpp
// 
// 简单语法分析器的SimpleAnalyzer程序入口点。


#include "ll_one_analyzer.h"

#include <iostream>
#include <vector>


using namespace std;
using namespace angelica;


// 判断输入串是否为给定文法的句子
void UseAnalyzerToJudge(LLOneAnalyzer& analyzer, vector<Symbol> input)
{
	string input_string;
	for (auto symbol : input) input_string += symbol;

	cout << "输入串：" << input_string << endl;

	bool input_is_sentence = analyzer.Judge(input);
	
	cout << "输入串" << input_string;
	cout << (input_is_sentence ? "是" : "不是");
	cout << "所给文法的句子。" << endl;
	cout << endl;
}


// 由于此实验内容较为简单，main函数也兼做词法分析器的功能。
int main()
{
	LLOneAnalyzer analyzer;
	
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "i", "+", "i" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "i", "+", "(", "i" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "i", "+", "i", ")" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "(", "*", ")" });
	UseAnalyzerToJudge(analyzer, vector<Symbol> { "(", "+", "i" });
}
