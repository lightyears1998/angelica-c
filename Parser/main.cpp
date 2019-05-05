#include "parser.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace angelica;


// �ӱ�׼�����ж�ȡԴ���룬��������ʷ���
int main()
{
	Parser parser;

	string input;
	{  // ��ȡ��׼���뵽input��ֱ������EOF
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
