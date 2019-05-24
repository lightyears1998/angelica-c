// main.cpp
// 
// 简单语法分析器的SimpleAnalyzer程序入口点。


#include "ll_one_analyzer.h"

#include <iostream>
#include <vector>


using namespace std;
using namespace angelica;


int main()
{
	LLOneAnalyzer analyzer;
	
	// 由于此实验内容较为简单，main函数也兼做词法分析器的功能。
	vector<Symbol> sentence{"i", "+", "i"};

	cout << (analyzer.Judge(sentence) ? "输入串i+i是该文法的句子。" : "输入串i+i不是该文法的句子。")
		 << endl;
}
