#include <iostream>
#include <string>

namespace angelica
{
	// �﷨����
	class Symbol
	{

	};
}

using namespace std;
using namespace angelica;

// �ӱ�׼�����ж�ȡԴ���룬��������ʷ���
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
