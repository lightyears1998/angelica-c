// main.cpp
//
// LLOneMaker的入口点。

#include "common.h"
#include "parser.h"

#include <iostream>
#include <queue>

using namespace std;
using namespace angelica;


int main()
{
	cout << "程序可将自动为LL(1)文法生成为LL(1)分析表，并分析输入串是否为给定文法的句子。" << endl;
	
	Parser parser;

	cout << "请输入LL(1)文法，按Ctrl+Z结束输入：" << endl;
}
