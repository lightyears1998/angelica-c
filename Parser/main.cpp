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

	vector<Symbol> vec;
	{
		for (size_t idx = 0; idx < input.length(); ++idx)
		{
			string token(1, input[idx]);  // ��token��ʼ��Ϊinput[idx]
			
			if (isspace(token[0])) {  // �˳��հ��ַ�
				continue;
			}

			if (isalpha(token[0])) {
				size_t cur = idx + 1;  // �������ĵ�һ���ַ����±�
				while (cur < input.length() && (isalpha(input[cur]) || isdigit(input[cur]))) {
					token += input[cur];
					cur += 1;
				}
				
				idx = cur - 1;
				vec.push_back(Symbol(SymbolType::ID, token));  // ����Ҫ�����Ƿ�Ϊ�ؼ���
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
				while (cur < input.length() && input[cur] != '"') {  // ������ת���ַ�
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
