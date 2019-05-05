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
	parser.Parse(input);

	vector<Symbol> vec(parser.GetSymbols());
	for (size_t i = 0; i < vec.size(); ++i) {
		cout << parser.GetSymbolString(vec[i]);
	}
}
