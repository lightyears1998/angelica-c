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

	// ���дʷ�����
	parser.Parse(input);
	vector<Symbol>vec(parser.GetSymbols());

	// �ڱ�׼����д�ӡ���ʷ���
	cout << parser.GetSymbolString(vec[0]);
	for (size_t i = 1; i < vec.size(); ++i) {
		cout << (vec[i].line_number != vec[i-1].line_number ? "\n" : " ");
		cout << parser.GetSymbolString(vec[i]) << vec[i].line_number << ':' << vec[i].column_number;
	}
}
