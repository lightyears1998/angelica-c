// main.cpp
// 
// ���﷨��������SimpleAnalyzer������ڵ㡣


#include "ll_one_analyzer.h"

#include <iostream>
#include <vector>


using namespace std;
using namespace angelica;


int main()
{
	LLOneAnalyzer analyzer;
	
	// ���ڴ�ʵ�����ݽ�Ϊ�򵥣�main����Ҳ�����ʷ��������Ĺ��ܡ�
	vector<Symbol> sentence{"i", "+", "i"};

	cout << (analyzer.Judge(sentence) ? "���봮i+i�Ǹ��ķ��ľ��ӡ�" : "���봮i+i���Ǹ��ķ��ľ��ӡ�")
		 << endl;
}
