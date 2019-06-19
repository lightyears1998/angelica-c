// main.cpp
//
// LLOneMaker的入口点。

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
	cout << "程序可将自动为LL(1)文法生成为LL(1)分析表，并分析输入串是否为给定文法的句子。" << endl;
	
	Parser parser(cin);
	LLOneBuilder builder(parser);

	cout << "请输入LL(1)文法，使用空格区分文法的左部和右部，每行输入一条产生式，按Ctrl+Z结束输入：" << endl;
	LLOneAnalyzer analyzer = builder.BuildAnalyzer();

	cout << "请输入单词符号串，用回车结束输入：" << endl;
	vector<Symbol> sentence = parser.ParseLineFromInputStream();
	cout << (analyzer.Judge(sentence) ? "单词符号串是所给文法的句子。" : "单词符号串不是所给文法的句子。" ) << endl;
}
