#include "parser.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace angelica;


// 从标准输入中读取源代码，并输出单词符号
int main()
{
	Parser parser;

	string input;
	{  // 读取标准输入到input，直到遇到EOF
		string line;
		while (getline(cin, line)) {
			input += line;
			input += '\n';
		}
	}

	// 进行词法分析
	parser.Parse(input);
	vector<Symbol>vec(parser.GetSymbols());

	// 在标准输出中打印单词符号
	cout << parser.GetSymbolString(vec[0]);
	for (size_t i = 1; i < vec.size(); ++i) {
		cout << (vec[i].line_number != vec[i-1].line_number ? "\n" : " ");
		cout << parser.GetSymbolString(vec[i]) << vec[i].line_number << ':' << vec[i].column_number;
	}
}
