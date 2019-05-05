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

	vector<Symbol> vec;
	{
		for (size_t idx = 0; idx < input.length(); ++idx)
		{
			string token(1, input[idx]);  // 将token初始化为input[idx]
			
			if (isspace(token[0])) {  // 滤除空白字符
				continue;
			}

			if (isalpha(token[0])) {
				size_t cur = idx + 1;  // 待分析的第一个字符的下标
				while (cur < input.length() && (isalpha(input[cur]) || isdigit(input[cur]))) {
					token += input[cur];
					cur += 1;
				}
				
				idx = cur - 1;
				vec.push_back(Symbol(SymbolType::ID, token));  // 还需要考虑是否为关键字
				continue;
			}

			if (isdigit(token[0])) {
				size_t cur = idx + 1;
				while (cur < input.length() && isdigit(input[cur])) {
					token += input[cur];
					cur += 1;
				}

				idx = cur - 1;
				vec.push_back(Symbol(SymbolType::INT, token));
				continue;
			}

			if (token[0] == '"') {
				token = "";
				size_t cur = idx + 1;
				while (cur < input.length() && input[cur] != '"') {  // 不考虑转义字符
					token += input[cur];
					cur += 1;
				}

				idx = cur;
				vec.push_back(Symbol(SymbolType::STRING, token));
				continue;
			}
		}
	}

	for (size_t idx = 0; idx < vec.size(); ++idx) {
		cout << vec[idx].ToString();
	}
}
