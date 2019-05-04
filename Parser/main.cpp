#include <iostream>
#include <string>

namespace angelica
{
	// 语法符号
	class Symbol
	{

	};
}

using namespace std;
using namespace angelica;

// 从标准输入中读取源代码，并输出单词符号
int main()
{
	string input;
	{
		string line;
		while (getline(cin, line)) {
			input += line;
			input += '\n';
		}
	}
	cout << input << endl;
}
